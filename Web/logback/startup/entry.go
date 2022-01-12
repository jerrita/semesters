package startup

import (
	"fmt"
	"logback/controller"
	"logback/util"

	"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

func EntryPoint(conf util.Config) {
	fmt.Printf("Server will run in %s:%d...\n", conf.Address, conf.Port)

	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()
	r.Use(cors.Default())

	// CROS Config

	// api 操作
	// register 请求，提供用户基本信息（JSON）
	r.POST("/api/register", controller.UserRegister)

	// 获取用户信息，需要 username 与 password
	r.POST("/api/getuser", controller.UserGet)

	err := r.Run(fmt.Sprintf("%s:%d", conf.Address, conf.Port))
	if err != nil {
		return
	}
}
