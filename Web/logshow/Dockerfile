FROM nginx:1.21.4-alpine

COPY dist /usr/share/nginx/html
EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]