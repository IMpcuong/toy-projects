package bot

import (
	"context"
	"fmt"
	"telebot/logger"
	"time"

	"github.com/google/go-github/v49/github"
)

type Report struct {
	Desc  string
	Date  string
	Tasks []Task
}

func (r Report) Stringify() string {
	strTasks := func(tasks []Task) string {
		var report string
		for _, t := range tasks {
			report += t.Stringify()
		}
		return report
	}(r.Tasks)

	return fmt.Sprintf("%s\n%s\n%s", r.Date, r.Desc, strTasks)
}

type Task struct {
	Status   string
	Data     string
	Owners   []string
	Deadline github.Timestamp
}

func (t Task) Stringify() string {
	d := t.Deadline.String()
	owners := func(arr []string) string {
		var urls string
		for _, a := range arr {
			urls += fmt.Sprintf("%s\n", a)
		}
		return urls
	}(t.Owners)

	return fmt.Sprintf("%s\n%s\n%s\n%s", t.Status, d, t.Data, owners)
}

func SetRateLimits(ctx context.Context, maximum int, client *github.Client) {
	rate, _, err := client.RateLimits(ctx)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Print(out)
	}
	if rate.Core.Limit > maximum {
		rate.Core.Limit = maximum
	}
}

func CollectTask(ctx context.Context, orgName string, client *github.Client) (tasks []Task) {
	org, _, err := client.Organizations.Get(ctx, orgName)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
	}
	if !org.GetHasOrganizationProjects() {
		logger.Error.Print("WIZ-Team currently has no opened projects")
	}

	// NOTE(doc):
	// + https://docs.github.com/en/rest/projects/projects?apiVersion=2022-11-28
	// + https://pkg.go.dev/github.com/google/go-github/v49/github#Organization

	// FIXME: Cannot retrieve list projects.
	projs, _, err := client.Organizations.ListProjects(ctx, orgName, &github.ProjectListOptions{State: "open"})
	fmt.Printf("=====> %#v\n", projs)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
	}
	for _, p := range projs {
		t := Task{}
		t.Status = p.GetState()
		t.Owners = append(t.Owners, p.GetOwnerURL())
		t.Deadline = p.GetCreatedAt()
		tasks = append(tasks, t)
	}
	return
}

func DailyReport(tasks []Task) (r Report) {
	day := time.Now().Day()
	month := time.Now().Month().String()
	year := time.Now().Year()
	today := fmt.Sprintf("%d-%s-%d", day, month, year)
	r.Desc = "DailyReport for WIZ-Team projects:\n"
	r.Date = today
	r.Tasks = tasks
	return
}
