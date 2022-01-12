package hlccd.flushbonading;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.qmuiteam.qmui.widget.QMUIProgressBar;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.net.URLConnection;

public class MainActivity extends AppCompatActivity {
    private EditText        edit;
    private TextView        ip;
    private TextView        ack;
    private TextView        pre;
    private TextView        name;
    private TextView        next;
    private QMUIProgressBar RP;
    private TextView        add;
    private TextView        RP_num;
    private TextView        sub;
    private ImageButton     stop;
    private ImageButton     pause;
    private ImageButton     begin;

    private File    file;
    private int     volume = 10;
    private Boolean change = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        edit   = findViewById(R.id.edit);
        ip     = findViewById(R.id.ip);
        ack    = findViewById(R.id.ack);
        pre    = findViewById(R.id.pre);
        name   = findViewById(R.id.name);
        next   = findViewById(R.id.next);
        RP     = findViewById(R.id.RP);
        add    = findViewById(R.id.add);
        RP_num = findViewById(R.id.RP_num);
        sub    = findViewById(R.id.sub);
        stop   = findViewById(R.id.stop);
        pause  = findViewById(R.id.pause);
        begin  = findViewById(R.id.begin);

        ip.setText(User.getUser().getIp());
        edit.setVisibility(View.GONE);
        ip.setVisibility(View.VISIBLE);
        stop.setVisibility(View.GONE);
        pause.setVisibility(View.GONE);
        begin.setVisibility(View.VISIBLE);
        RP_num.setText("音量:" + volume);
        RP.setProgress(volume * 4);
        ack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (change) {
                    ack.setText("确认");
                    ip.setVisibility(View.GONE);
                    edit.setVisibility(View.VISIBLE);
                    change = false;
                } else {
                    ack.setText("修改");
                    User.getUser().setIp(edit.getText().toString());
                    ip.setText(User.getUser().getIp());
                    ip.setVisibility(View.VISIBLE);
                    edit.setVisibility(View.GONE);
                    change = true;
                }
            }
        });
        pre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendPre();
            }
        });
        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendNext();
            }
        });
        begin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendBegin();
                stop.setVisibility(View.VISIBLE);
                pause.setVisibility(View.VISIBLE);
                begin.setVisibility(View.GONE);
            }
        });
        pause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendPause();
                stop.setVisibility(View.VISIBLE);
                pause.setVisibility(View.GONE);
                begin.setVisibility(View.VISIBLE);
            }
        });
        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendStop();
                stop.setVisibility(View.GONE);
                pause.setVisibility(View.GONE);
                begin.setVisibility(View.VISIBLE);
            }
        });
        add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (volume < 25) {
                    volume++;
                    RP_num.setText("音量:" + volume);
                    RP.setProgress(volume * 4);
                    sendVolume();
                }
            }
        });
        sub.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (volume > 0) {
                    volume--;
                    RP_num.setText("音量:" + volume);
                    RP.setProgress(volume * 4);
                    sendVolume();
                }
            }
        });
    }

    private void sendVolume() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/volume", "volume=" + volume);
            }
        }).start();
    }

    private void sendPre() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/play", "method=pre");
            }
        }).start();
    }

    private void sendNext() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/play", "method=next");
            }
        }).start();
    }

    private void sendBegin() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/play", "method=play");
            }
        }).start();
    }

    private void sendPause() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/play", "method=pause");
            }
        }).start();
    }

    private void sendStop() {
        if (User.getUser().getIp().equals("点击选择设备ip")) {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                sendPost("http://" + User.getUser().getIp() + "/api/play", "method=pause");
            }
        }).start();
    }

    public static String sendPost(String url, String param) {
        PrintWriter    out    = null;
        BufferedReader in     = null;
        String         result = "";
        try {
            URL realUrl = new URL(url);
            // 打开和URL之间的连接
            URLConnection conn = realUrl.openConnection();
            // 设置通用的请求属性
            conn.setRequestProperty("accept", "*/*");
            conn.setRequestProperty("connection", "Keep-Alive");
            conn.setRequestProperty("user-agent",
                    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
            // 发送POST请求必须设置如下两行
            conn.setDoOutput(true);
            conn.setDoInput(true);
            // 获取URLConnection对象对应的输出流
            out = new PrintWriter(conn.getOutputStream());
            // 发送请求参数
            out.print(param);
            // flush输出流的缓冲
            out.flush();
            // 定义BufferedReader输入流来读取URL的响应
            in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                result += line;
            }
        } catch (Exception e) {
            System.out.println("发送 POST 请求出现异常！" + e);
            e.printStackTrace();
        }
        //使用finally块来关闭输出流、输入流
        finally {
            try {
                if (out != null) {
                    out.close();
                }
                if (in != null) {
                    in.close();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
        System.out.println("url=" + url + "?" + param);
        System.out.println("result=" + result);
        return result;
    }
}