package model

import (
	"logback/util"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

var DB *gorm.DB

func DBInit() error {
	db, err := gorm.Open("sqlite3", util.Conf.DBPath)

	db.AutoMigrate(&User{})

	DB = db
	return err
}
