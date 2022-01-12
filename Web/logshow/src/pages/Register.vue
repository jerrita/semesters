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
        account: "",
        password: "",
        sex: true,
        hobby: "",
        introduce: "",
      },
      rules: {
        account: {
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
          // 输入验证通过，请求开始
          this.$axios
            .post("api/register", {
              username: this.form.account,
              password: md5(this.form.password),
              sex: this.form.sex,
              hobby: this.form.hobby,
              introduce: this.form.introduce,
            })
            .then((res) => {
              // alert(res.data.msg);
              console.log(res.data);
              if (res.data.status == 0) {
                alert("注册成功！即将跳转至主页...");

                this.cookies.set("username", this.form.account);
                this.cookies.set("password", md5(this.form.password));

                this.$router.push("/");
              } else {
                alert(res.data.msg);
              }
            })
            .catch((err) => {
              console.log(err);
              alert("后端失联，请联系管理员解决！");
            });
        } else {
          console.log("error submit");
          return false;
        }
      });
    },
    gotoLogin() {
      this.$router.push("/login");
    },
  },
};
</script>

<template>
  <el-card class="box-card">
    <template #header>
      <div class="card-header">
        <span>注册</span>
      </div>
    </template>

    <el-form ref="form" :model="form" :rules="rules" label-width="80px">
      <el-form-item label="用户名" prop="account">
        <el-input v-model="form.account" placeholder="请输入用户名"></el-input>
      </el-form-item>
      <el-form-item label="密码" prop="password">
        <el-input
          v-model="form.password"
          placeholder="请输入密码 (不少于8位)"
          show-password
        ></el-input>
      </el-form-item>
      <el-form-item label="性别">
        <el-radio-group v-model="form.sex" size="medium">
          <el-radio-button label="true">男</el-radio-button>
          <el-radio-button label="false">女</el-radio-button>
        </el-radio-group>
      </el-form-item>
      <el-form-item label="爱好">
        <el-input v-model="form.hobby"></el-input>
      </el-form-item>
      <el-form-item label="个人简介">
        <el-input v-model="form.introduce" type="textarea" :rows="6"></el-input>
      </el-form-item>

      <el-form-item>
        <el-space>
          <el-button type="primary" @click="onSubmit('form')">注册</el-button>
          <el-link @click="gotoLogin">已有账号？点击登录</el-link>
        </el-space>
      </el-form-item>
    </el-form>
  </el-card>
</template>

<style>
</style>
