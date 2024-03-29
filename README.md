# GXU_Tools
广西大学校园网自动登录 自动评教 自动查考试、信息查询

---
## 部分界面
![校园网登录界面](https://036aaa68.telegraph-image-2r3.pages.dev/file/6a196661fa7a9ad1eecbf.png)
![教务系统界面](https://036aaa68.telegraph-image-2r3.pages.dev/file/f6019b05f7ab293e49318.png)





## 碎碎念
### 关于选型
一开始只想做个自动登录器，顺便练一下英语，就选了个几乎没啥中文资料的gui框架，毕竟多恶心的框架写个小登录器总不碍事。再加上wxWidgets静态编译一个helloword只有4m，用来写小工具也是不错的。不过到后面因为没法实现直接调api登教务系统，导致这个模块只能使用webview，一套写下来发现确实大家不用wxWidgets用QT是有原因的。加上后面有点不想写了，代码十分答辩，甚至源代码都是直接在网页端上传的而不是用Git，开源只是让大家放心用。
另外libhv是一个非常好用的c++网络库，谁用谁知道，强烈推荐。

### 一些有点用的东西
代码写的一坨，这里分享一些我的发现吧，如果有后来者，希望能为你提供一些便利。
#### 登录
西大用的是方正的系统，使用他们自己实现的rsa算法进行加密，看了一下应该只是密钥比原版的短，其他没有区别，github中有人使用python重写了一遍实现，我死活登不上去，直接webview了
#### 评教
使用webview构建评教请求很简单，直接调网站的js就好，如果想自行构建有点难度，请求中很多项的意思不明确，再加上请求要带上一段网页中的id（类似csrf），还是调网站自己的js容易点。
另外，评教的保存接口没有太多校验：当你已经提交对某个老师的评价后，本是不能改动的，但是可以通过js向评教的保存接口发送该条数据，这么操作就会让这个老师处于“未评价”状态，此时又可以提交新的评价了。（其他模块应该都是窟窿，只是没人研究而已）

下面是评教的js脚本

``` javascript
async () => {
const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));
await sleep(900);
$(".ui-pg-selbox").val(5000);
await sleep(900);
$(".ui-pg-selbox").change();
await sleep(900);
var firstCellList = $("tbody:first tr").not(':first').find("td:visible:first");
var teCellList = $("tbody:first tr:visible").find('td:visible:eq(1)');
for (var i = 0; i < firstCellList.length; i++) {
    var cell = $("tbody:first tr").not(':first').find("td:visible:first").eq(i);
    $("tbody:first tr").not(':first').find("td:visible:first").eq(i).click();
    await sleep(500);

	  if (cell.text() !== "提交") {
        $(".radio-inline.input-xspj.input-xspj-1 input").prop("checked", true);
        $(".radio-inline.input-xspj.input-xspj-2 input:first").click();
        var bfztxfs = $("#bfztxfs").val();
        var flagTf = true;
        var bfzpf;
        var panel_pjdx = $.find("div.panel-pjdx");
        if (bfztxfs == "2") {
            bfzpf = calculatePjmbPjzf2(panel_pjdx);
        } else {
            bfzpf = calculatePjmbPjzf(panel_pjdx);
        }
        var xspj_body = $("div.xspj-body");
        var jxb_id = $(xspj_body).data("jxb_id");
        var jgh_id = $(xspj_body).data("jgh_id");
        jQuery.ajaxSetup({ async: false });
        jQuery.post(_path + '/xspjgl/xspj_cxSftf.html', { bfzpf: bfzpf, jxb_id: jxb_id, jgh_id: jgh_id }, function (data) {
            if (data != 0) {
                flagTf = false;
                $.alert("同学，存在分数与当前评价分相同，请做调整");
                return flagTf;
            }
        }, 'json');

        var dataMap = buildRequestMap.call(this) || {};
        dataMap["tjzt"] = "0";
        jQuery.ajax({
            url: _path + "/xspjgl/xspj_tjXspj.html",
            type: "post",
            dataType: "json",
            data: dataMap,
            async: false,

        });
        await sleep(200);
    }
}
})();

```

## 致谢
wxWidgets: https://github.com/wxWidgets/wxWidgets </br>
wxFormBuilder：https://github.com/wxFormBuilder/wxFormBuilder </br>
libhv： https://github.com/ithewei/libhv </br>
广西大学学生科技协会（B站）关注科协谢谢喵~：https://space.bilibili.com/187447234



---
## 软件说明书


### 零.关于软件
本软件是个人编写的免费开源软件，可能会报毒，请放心加入白名单。
个人能力有限，写得比较潦草，不保证没有内存泄露与程序崩溃问题。重启电脑解决大部分问题: )
软件记住的账号密码是“明文”保存在软件所在文件夹下的config.ini中。介意的话请不要使用本软件(有空可能会更新加密)，分享软件时请不要带上config.ini和examData.json(当前学期的考试信息)。


### 一.启动
软件第一次启动会弹出“关于窗口”，直接关掉就好。说“弃用前关闭开机自启”是因为删除本软件不会自动清除注册表，需要手动关闭开机自启，不过像火绒等软件都有注册表清理功能，关不关开机自启问题不大。
“关于窗口”后面就是“校园网登录窗口”，操作和网页登录差不多。
### 二.校园网登录窗口
这个窗口挺简单的就不详细写了，不过注意:1.软件不会提示账号密码是否正确，如果在不断网时点击“登录”半分钟后仍然提示“未连接”，请检查账号密码是否正确。2.软件没有查询剩余流量功能，使用校园网的同学请留意流量消耗情况。
若勾选了开机启动，下次开机自启的软件就不会弹出“校园网登录页面”了，而是直接根据记住的账号密码，在后台进行自动登录，减少打扰。

题外话，学校的DNS时不时就出问题，如果QQ能登但是网页不能开，更换114.114.114.114等其他可用的DNS即可解决

### 三.教务系统页面
输账号密码直接用就行。
关于页面难看:本来没打算做这个功能，闭眼睛乱写的，写得确实潦草。
上面的表格是考试信息，按考试开始先后排序。
中间是成绩表格，注意:有些课只有“作业成绩”，“实操成绩”等项目而没有“平时成绩”这一项，所以软件里只显示总评，不显示的项目请登录教务系统查看。
下面是一个内嵌的教务系统页面，用来查看当前状态，比如账号密码错了，自动评教进度等。(图省事直接扔个网页过来了，难看确实难看)。

关于自动评教:默认全部给最高分，不留评语。如果对哪个老师又特殊的感情可以先去教务系统先提交对ta的评价再回来自动评教。
自动评教时，只要在下面的教务系统页面看到脚本在逐个老师评价就好。脚本评价过的老师显示“未评”是正常现象，等脚本评完所有老师后刷新页面(或者再点一次“自动评教”也行)就能看到所有老师都是“已评”状态了。

关于自动查询考试与成绩信息:软件会每三十分钟自动查询当前学期的考试与成绩信息，如果有新的考试或成绩，会发通知提醒大家。自动查询是默认开启的不需要进行任何设置。

关于手动查询考试与成绩:有时候会点了没反应，多试几次。


