package pkg

import "net/url"

type Autobot struct {
	Enable bool
	Auth   string
	Data   string
	Dest   *url.URL
}
