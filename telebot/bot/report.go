package bot

import (
	"context"
	"fmt"
	"telebot/logger"
	"time"

	"github.com/google/go-github/v49/github"
	"github.com/shurcooL/githubv4"
)

type Report struct {
	Desc     string
	Date     string
	Projects []Project
}

func (r Report) Stringify() string {
	strTasks := func(projects []Project) string {
		var report string
		for _, t := range projects {
			report += t.Stringify()
		}
		return report
	}(r.Projects)

	return fmt.Sprintf("%s\n%s\n%s", r.Date, r.Desc, strTasks)
}

type Project struct {
	ID       string
	URL      string
	Title    string
	Status   string
	Data     string
	Owners   []string
	Deadline github.Timestamp
}

func (t Project) Stringify() string {
	d := t.Deadline.String()
	owners := func(arr []string) string {
		var urls string
		for _, a := range arr {
			urls += fmt.Sprintf("%s\n", a)
		}
		return urls
	}(t.Owners)

	data := fmt.Sprintf("%s\n%s\n%s\n%s\n%s\n%s\n%s", t.ID, t.URL, t.Title, t.Status, d, t.Data, owners)
	return data
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

type Projects struct {
	Organization struct {
		ProjectsV2 struct {
			Nodes []struct {
				ID    string `graphql:"id"`
				URL   string `graphql:"url"`
				Title string `graphql:"title"`
			} `graphql:"nodes"`
		} `graphql:"projectsV2(first: $limit)"`
	} `graphql:"organization(login: $orgName)"`
}

func CollectTaskV4(ctx context.Context, orgName string, limit int, client *githubv4.Client) (projects []Project, err error) {
	var projectsV4 Projects
	params := map[string]any{
		"orgName": githubv4.String(orgName),
		"limit":   githubv4.Int(limit),
	}
	err = client.Query(ctx, &projectsV4, params)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Print(out)
		return projects, nil
	}

	for _, p := range projectsV4.Organization.ProjectsV2.Nodes {
		t := Project{}
		t.ID = p.ID
		t.URL = p.URL
		t.Title = p.Title
		// FIXME: Retrieve correct deadline.
		t.Deadline = github.Timestamp{}
		projects = append(projects, t)
	}
	return
}

func CollectTaskV3(ctx context.Context, orgName string, client *github.Client) (tasks []Project, err error) {
	org, _, err := client.Organizations.Get(ctx, orgName)
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
		return nil, err
	}
	if !org.GetHasOrganizationProjects() {
		logger.Error.Print("WIZ-Team currently has no opened projects")
		return nil, err
	}

	// NOTE(doc):
	// + https://docs.github.com/en/rest/projects/projects?apiVersion=2022-11-28
	// + https://pkg.go.dev/github.com/google/go-github/v49/github#Organization

	// FIXME: Projects that belong to our organization cannot be retrieved using a JSON query alone.
	projects, _, err := client.Organizations.ListProjects(ctx, orgName, &github.ProjectListOptions{State: "open"})
	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
	}

	for _, p := range projects {
		t := Project{}
		t.Status = p.GetState()
		t.Owners = append(t.Owners, p.GetOwnerURL())
		t.Deadline = p.GetCreatedAt()
		tasks = append(tasks, t)
	}
	return
}

func DailyReport(projects []Project) (r Report) {
	day := time.Now().Day()
	month := time.Now().Month().String()
	year := time.Now().Year()
	today := fmt.Sprintf("%d-%s-%d", day, month, year)
	r.Desc = "DailyReport for WIZ-Team projects:\n"
	r.Date = today
	r.Projects = projects
	return
}
