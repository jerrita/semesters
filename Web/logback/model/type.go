package model

import (
	"github.com/jinzhu/gorm"
)

type LoginError int

const (
	UserNotFound LoginError = iota + 1
	UserExists
	UserPasswordWrong
	UserInvalid
)

// User 用户存储模式
type User struct {
	gorm.Model
	Username string `json:"username"`
	Password string `json:"password"`
	Sex      bool   `json:"sex"`
	Hobby    string `json:"hobby"`
	Intro    string `json:"introduce"`
}

type LoginStruct struct {
	Username string `json:"username"`
	Password string `json:"password"`
}
