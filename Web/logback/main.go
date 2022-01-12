package main

import (
	"logback/model"
	"logback/startup"
	"logback/util"
)

func main() {
	// 读取配置
	conf, err := util.ConfInit()
	if err != nil {
		return
	}

	// 数据库初始化
	err = model.DBInit()
	if err != nil {
		return
	}

	// 路由初始化
	startup.EntryPoint(conf)
}
