# 使用 Drone 进行缓存，跳过此步
# FROM golang:latest as builder
# COPY . .
# RUN CGO_ENABLED=1 go build -ldflags="-w -s" .

# FROM alpine:latest
FROM registry.cn-hangzhou.aliyuncs.com/jerrita/image:base-debian

WORKDIR /app
COPY logback /app

EXPOSE 8080
CMD ["./logback"]
