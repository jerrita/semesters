import { createApp } from "vue";
import axios from "axios";
import App from "./App.vue";
import defaultRouter from "./router/main";

const app = createApp(App);
app.config.globalProperties.$axios = axios.create({
  baseURL: "",
});
app.use(defaultRouter).mount("#app");
