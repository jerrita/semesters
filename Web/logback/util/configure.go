package util

import (
	"flag"
)

type Config struct {
	Address string
	Port    int
	DBPath  string
}

var Conf Config

func ConfInit() (Config, error) {

	str := flag.String("addr", "0.0.0.0", "Address to listen")
	port := flag.Int("port", 8080, "Port to listen")
	flag.Parse()

	Conf = Config{
		*str,
		*port,
		"user.db",
	}

	return Conf, nil
}
