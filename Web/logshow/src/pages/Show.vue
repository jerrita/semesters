<template>
  <el-card class="box-card">
    <template #header>
      <div class="card-header">
        <span>用户信息</span>
      </div>
    </template>

    <el-space direction="vertical" class="show">
      <div class="show">用户名：{{ user.username }}</div>
      <div class="show">性别：{{ user.sex ? "男" : "女" }}</div>
      <div class="show">爱好：{{ user.hobby }}</div>
      <div class="show">个人简介：{{ user.intro }}</div>
      <tr />
      <el-button size="medium" @click="signout">退出登录</el-button>
    </el-space>
  </el-card>
</template>

<style>
.show {
  text-align: center;
  width: 100%;
}
</style>

<script>
import { useCookies } from "vue3-cookies";
import { useRouter } from "vue-router";

export default {
  setup() {
    const { cookies } = useCookies();
    console.log(cookies.get("username"));
    if (cookies.get("username") == null) {
      console.log("Seems you do not login yet, redirect to login page.");
      useRouter().push("/login");
    }
    return { cookies };
  },
  mounted() {
    // 合法性检测
    let username = this.cookies.get("username");
    let password = this.cookies.get("password");
    this.$axios
      .post("api/getuser", {
        username: username,
        password: password,
      })
      .then((res) => {
        if (res.data.status == 0) {
          console.log(res.data);
          this.user = {
            username: username,
            sex: res.data.sex,
            hobby: res.data.hobby,
            intro: res.data.intro,
          };
        } else {
          // 登录失效，跳转至登录页面
          this.cookies.remove("username");
          this.$router.push("/login");
        }
      })
      .catch((err) => {
        alert('后端服务器未启动！请联系管理员。')
        console.log(err);
      });
  },
  data() {
    return {
      user: {
        username: "",
        sex: true,
        hobby: "",
        intro: "",
      },
    };
  },
  methods: {
    signout() {
      this.cookies.remove("username");
      this.$router.push("/login");
    },
  },
};
</script>