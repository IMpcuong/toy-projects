package main

import (
	"fmt"
)

func main() {
	m := map[int]int{1: 1, 10: 3, 32: 54, 82: 43, 3: 242}
	ans := func(m map[int]int) map[int]int {
    mCloned := func() map[int]int {
      mTmp := make(map[int]int, len(m))
      for k, v := range m {
        mTmp[k] = v
      }
      return mTmp
    }()
		for k := range mCloned {
			if k < 30 {
				delete(mCloned, k)
			}
		}
		return mCloned
	}(m)
	fmt.Printf("%+v\n", m)
	fmt.Printf("%+v\n", ans)
}
