package bot

import (
	"context"
	"encoding/json"
	"fmt"
	"telebot/logger"
	"time"

	"github.com/google/go-github/v49/github"
	"github.com/graphql-go/graphql"
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

const PROJECT_QUERY string = `
query($organization: String! $number: Int!){
	organization(login: $organization){
		projectV2(first: $number) {
			id
			url
			name
			body
		}
	}
}
`

func ExecGraphQL(query string, maxProjects int) ([]*github.Project, error) {
	fields := graphql.Fields{
		"project": &graphql.Field{
			Type: graphql.NewObject(graphql.ObjectConfig{
				Name: "Project",
				Fields: graphql.Fields{
					"id":   &graphql.Field{Type: graphql.Int},
					"url":  &graphql.Field{Type: graphql.String},
					"name": &graphql.Field{Type: graphql.String},
					"body": &graphql.Field{Type: graphql.String},
				},
			}),
			Args: graphql.FieldConfigArgument{
				"organization": &graphql.ArgumentConfig{Type: graphql.String},
				"number":       &graphql.ArgumentConfig{Type: graphql.Int},
			},
			Resolve: func(p graphql.ResolveParams) (interface{}, error) {
				last, ok := p.Args["number"].(int64)
				if !ok {
					return nil, fmt.Errorf("Missing maximum projects needed!\n")
				}
				projects := []*github.Project{
					{ID: &last},
					{ID: &last},
				}
				return projects, nil
			},
		},
	}
	rootQuery := graphql.ObjectConfig{
		Name:   "RootQuery",
		Fields: fields,
	}
	schemaConfig := graphql.SchemaConfig{
		Query: graphql.NewObject(rootQuery),
	}
	schema, err := graphql.NewSchema(schemaConfig)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Print(out)
	}
	result := graphql.Do(graphql.Params{
		Schema:        schema,
		RequestString: query,
	})
	if len(result.Errors) > 0 {
		out := logger.CustomError(logger.RuntimeError, result.Errors[len(result.Errors)-1])
		logger.Error.Print(out)
	}

	jsonString, _ := json.MarshalIndent(result.Data, "", "    ")
	fmt.Printf("%s\n", jsonString)
	return nil, nil
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

	// FIXME: List of projects from are belonged to our organization cannot be retrieved using JSON query.
	projects, _, err := client.Organizations.ListProjects(ctx, orgName, &github.ProjectListOptions{State: "open"})
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
	}

	for _, p := range projects {
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
