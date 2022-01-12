/// <reference types="vite/client" />
// import defaultRouter from "./router/main";

declare module "*.vue" {
  import { DefineComponent } from "vue";
  // eslint-disable-next-line @typescript-eslint/no-explicit-any, @typescript-eslint/ban-types
  const component: DefineComponent<{}, {}, any>;
  export default component;
}

// declare module "vue/types/vue" {
//   interface Vue {
//     $router: typeof defaultRouter;
//   }
// }
