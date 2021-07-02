all: clean deps build

clean:
	rm -rf go.mod go.sum

deps:
	go mod init wserver
	go mod tidy -v

build:
	go build main.go
