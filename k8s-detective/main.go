package main

import (
	"context"
	"fmt"
	"path/filepath"
	"strings"
	"time"

	"k8s.io/apimachinery/pkg/api/errors"
	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/client-go/kubernetes"
	"k8s.io/client-go/tools/clientcmd"
	"k8s.io/client-go/util/homedir"
	//
	// Uncomment to load all auth plugins
	// _ "k8s.io/client-go/plugin/pkg/client/auth"
	//
	// Or uncomment to load specific auth plugins
	// _ "k8s.io/client-go/plugin/pkg/client/auth/oidc"
)

// go build -o detective .
// file ./detective # Output: ./detective: Mach-O 64-bit executable

// GOOS=linux GOARCH=amd64 go build -o detective .

func main() {
	var kubeConfigLocation string
	kubeConfigLocation = homedir.HomeDir()
	if kubeConfigLocation == "" {
		panic("ERROR: No $HOME which contains .kube/config file was found")
	}
	_configFile := ".kube/config"
	kubeConfigLocation = filepath.Join(kubeConfigLocation, _configFile)

	// Use the current context in kubeconfig.
	config, err := clientcmd.BuildConfigFromFlags("", kubeConfigLocation)
	if err != nil {
		panic(err.Error())
	}

	// Create the client-set.
	clientSet, err := kubernetes.NewForConfig(config)
	if err != nil {
		panic(err.Error())
	}
	for {
		pods, err := clientSet.CoreV1().Pods("").List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			panic(err.Error())
		}
		fmt.Printf("There are %d pods in the cluster\n", len(pods.Items))

		nsList, _ := clientSet.CoreV1().Namespaces().List(context.TODO(), metav1.ListOptions{}) // Omitting error.
		for _, ns := range nsList.Items {
			ns := ns.GetName()
			if !strings.Contains(ns, "tool") {
				continue
			}

			// Examples for error handling:
			// - Use helper functions like e.g. errors.IsNotFound().
			// - And/or cast to StatusError and use its properties like e.g. ErrStatus.Message.
			podList, err := clientSet.CoreV1().Pods(ns).List(context.TODO(), metav1.ListOptions{})
			if errors.IsNotFound(err) {
				fmt.Printf("Namespace %s didn't contain any pods\n", ns)
			} else if statusError, isStatus := err.(*errors.StatusError); isStatus {
				fmt.Printf("Error getting all pods in namespace %s: %v\n", ns, statusError.ErrStatus.Message)
			} else if err != nil {
				panic(err.Error())
			}

			for _, pod := range podList.Items {
				pName := pod.GetName()
				pKind := pod.GetObjectKind()
				pLabels := pod.GetLabels()
				pUID := pod.GetUID()
				pStatus := pod.Status.String()
				fmt.Printf("Name: %s\nKind: %#v\nLabels: %#v\nUID: %v\nStatus: %s\n---\n", pName, pKind, pLabels, pUID, pStatus)
			}
		}

		time.Sleep(8 * time.Second)
	}
}
