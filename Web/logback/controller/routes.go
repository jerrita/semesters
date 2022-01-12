package controller

import (
	"logback/model"
	"net/http"

	"github.com/gin-gonic/gin"
)

// 用户注册
func UserRegister(c *gin.Context) {

	// 获取参数
	usr := model.User{}
	err := c.ShouldBindJSON(&usr)

	if err != nil || usr.Username == "" || len(usr.Password) <= 8 {
		c.JSON(http.StatusOK, gin.H{
			"status": model.UserInvalid,
			"msg":    "Bad Request",
		})
		return
	}

	// 判断用户是否存在
	var u model.User
	model.DB.Find(&u, "username=?", usr.Username)
	if u.ID != 0 {
		c.JSON(http.StatusOK, gin.H{
			"status": model.UserExists,
			"msg":    "User exists!",
		})
		return
	}

	// 用户不存在，更新数据库
	model.DB.Create(&usr)

	c.JSON(http.StatusOK, gin.H{
		"status": 0,
		"msg":    "Register success!",
	})
}

// 获取已注册的用户信息
func UserGet(c *gin.Context) {

	// 获取参数
	usr := model.LoginStruct{}
	c.ShouldBindJSON(&usr)

	// 判断用户是否存在
	var u model.User
	model.DB.Find(&u, "username=?", usr.Username)
	if u.ID == 0 {
		c.JSON(http.StatusOK, gin.H{
			"status": model.UserNotFound,
			"msg":    "User Not Found!",
		})
		return
	}

	// 用户存在，比对信息
	if u.Password != usr.Password {
		c.JSON(http.StatusOK, gin.H{
			"status": model.UserPasswordWrong,
			"msg":    "Wrong Password!",
		})
		return
	}

	// 一切就绪，返回用户信息
	c.JSON(http.StatusOK, gin.H{
		"status":   0,
		"username": u.Username,
		"sex":      u.Sex,
		"hobby":    u.Hobby,
		"intro":    u.Intro,
		"msg":      "Success!",
	})
}
