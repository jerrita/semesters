<script>
import { useCookies } from "vue3-cookies";
import md5 from "js-md5";

export default {
  setup() {
    const { cookies } = useCookies();
    return { cookies };
  },
  data() {
    return {
      form: {
        username: "",
        password: "",
      },
      rules: {
        username: {
          required: true,
          message: "请输入用户名",
          trigger: "blur",
        },
        password: [
          {
            required: true,
            message: "请输入密码",
            trigger: "blur",
          },
          {
            min: 8,
            message: "密码长度需大于8位",
            trigger: "blur",
          },
        ],
      },
    };
  },
  methods: {
    onSubmit(formName) {
      console.log("Submit Fire!");

      this.$refs[formName].validate((valid) => {
        if (valid) {
          this.$axios
            .post("api/getuser", {
              username: this.form.username,
              password: md5(this.form.password),
            })
            .then((res) => {
              if (res.data.status == 0) {
                alert("登陆成功！即将返回主页...");

                this.cookies.set("username", this.form.username);
                this.cookies.set("password", md5(this.form.password));

                this.$router.push("/");
              } else {
                alert(res.data.msg);
                console.log(res.data.msg);
              }
            })
            .catch((err) => {
              alert('后端服务器未启动！请联系管理员。')
              console.log(err);
            });
        } else {
          console.log("error submit");
          return false;
        }
      });
    },
    gotoRegister() {
      this.$router.push("/register");
    },
  },
};
</script>

<template>
  <el-card class="box-card">
    <template #header>
      <div class="card-header">
        <span>登陆</span>
      </div>
    </template>

    <el-form ref="form" :model="form" :rules="rules" label-width="80px">
      <el-form-item label="用户名" prop="username">
        <el-input v-model="form.username"></el-input>
      </el-form-item>
      <el-form-item label="密码" prop="password">
        <el-input v-model="form.password" show-password></el-input>
      </el-form-item>

      <el-form-item>
        <el-space>
          <el-button type="primary" @click="onSubmit('form')">登录</el-button>
          <el-link @click="gotoRegister">还没有账号？点击注册</el-link>
        </el-space>
      </el-form-item>
    </el-form>
  </el-card>
</template>