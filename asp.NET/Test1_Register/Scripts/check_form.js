function checkUsername()
{
    var username = document.getElementById("username");
    var usernameTip = document.getElementById("username_tip");

    var reg = /^[a-z]{6,10}$/;
    //if (!reg.test(username.value) || username.value == "wustzz") {

    if (!reg.test(username.value) || !checkWustzz(username.value)) {
        usernameTip.innerHTML = "6~10个小写字母，且不能为\"wustzz\"";
        return false;
    } else {
        usernameTip.innerHTML = "OK";
        return true;
    }
}

function checkWustzz(username) {
    var success = false;
    $.ajax({
        type: "POST",
        url: "/Register/CheckWustzz",
        data: { "username": username },
        async: false,
        success: function (sesponseTest) {
            if (sesponseTest == "True") {
                success = true;
            }
            return;
        }
    });
    return success;
}

function checkPassword()
{
    var password = document.getElementById("password");
    var passwordTip = document.getElementById("password_tip");

    var reg = /^\d{6}$/;
    if (!reg.test(password.value)) {
        passwordTip.innerHTML = "6位数字";
        return false;
    } else {
        passwordTip.innerHTML = "OK";
        return true;
    }
}

function checkConfirm()
{
    var password = document.getElementById("password");
    var confirm = document.getElementById("confirm_password");
    var confirmTip = document.getElementById("confirm_tip");

    if (confirm.value == "") {
        confirmTip.innerHTML = "不能为空";
        return false;
    } else if (confirm.value != password.value) {
        confirmTip.innerHTML = "输入不一致";
        return false;
    } else {
        confirmTip.innerHTML = "OK";
        return true;
    }
}

function checkEmail()
{
    var email = document.getElementById("email");
    var emailTip = document.getElementById("email_tip");

    var reg = /^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/;
    if (!reg.test(email.value)) {
        emailTip.innerHTML = "地址不合法";
        return false;
    } else {
        emailTip.innerHTML = "OK";
        return true;
    }
}

function checkMobile()
{
    var mobile = document.getElementById("mobile");
    var mobileTip = document.getElementById("mobile_tip");

    var reg = /^1569\d{7}$/;
    if (!reg.test(mobile.value)) {
        mobileTip.innerHTML = "1569开头，11位数字";
        return false;
    } else {
        mobileTip.innerHTML = "OK";
        return true;
    }
}

function checkBirthYM()
{
    var birth = document.getElementById("datepicker");
    var birthTip = document.getElementById("birthYM_tip");

    var reg = /^(January|February|March|April|May|June|July|August|September|October|November|December) \d{4}$/;
    if (!reg.test(birth.value)) {
        birthTip.innerHTML = "输入错误，请用选择器";
        return false;
    } else {
        birthTip.innerHTML = "OK";
        return true;
    }
}

function checkAll()
{
    return checkUsername() &&
        checkConfirm() &&
        checkPassword() &&
        checkConfirm() &&
        checkEmail() &&
        checkMobile() &&
        checkBirthYM();
}