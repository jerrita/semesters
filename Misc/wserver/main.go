package main

import (
	"github.com/gin-gonic/gin"
)

func main() {
	var msg string

	r := gin.Default()

	r.LoadHTMLGlob("./htdocs/*")

	r.GET("/", func(c *gin.Context) {
		c.HTML(200, "index.html", nil)
	})

	r.GET("/hello", func(c *gin.Context) {
		if c.Query("name") == "" {
			msg = "This is a simple dynamic page. You can tell me your name."
		} else {
			msg = "Hello " + c.Query("name")
		}

		c.HTML(200, "hello.html", gin.H{
			"msg": msg,
		})
	})

	err := r.Run()
	if err != nil {
		return
	} // listen and serve on 0.0.0.0:8080
}
