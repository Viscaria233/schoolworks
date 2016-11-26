function checkTitle() {
    var input = document.getElementById("Title");
    var msg = document.getElementById("TitleMsg");
    if (input.value == "") {
        msg.innerHTML = "Title 字段是必需的。";
        input.className = "input-validation-error";
        return false;
    } else {
        msg.innerHTML = "";
        input.className = "text-box single-line";
        return true;
    }
}

function checkReleaseDate() {
    var input = document.getElementById("ReleaseDate");
    var msg = document.getElementById("ReleaseDateMsg");
    if (input.value == "") {
        msg.innerHTML = "ReleaseDate 字段是必需的。";
        input.className = "input-validation-error";
        return false;
    } else {
        msg.innerHTML = "";
        input.className = "text-box single-line";
        return true;
    }
}

function checkGenre() {
    var input = document.getElementById("Genre");
    var msg = document.getElementById("GenreMsg");
    if (input.value == "") {
        msg.innerHTML = "Genre 字段是必须必需的。"
        input.className = "input-validation-error";
        return false;
    } else {
        msg.innerHTML = ""
        input.className = "text-box single-line";
        return true;
    }
}

function checkPrice() {
    var input = document.getElementById("Price");
    var msg = document.getElementById("PriceMsg");
    if (input.value == "") {
        msg.innerHTML = "Price 字段是必需的。";
        input.className = "input-validation-error";
        return false;
    } else {
        msg.innerHTML = "";
        input.className = "text-box single-line";
        return true;
    }
}

function checkRating() {
    var input = document.getElementById("Rating");
    var msg = document.getElementById("RatingMsg");
    var reg = /^\w{0,5}$/;
    if (!reg.test(input.value)) {
        msg.innerHTML = "字段 Rating 必须是最大长度为5的字符串。"
        input.className = "input-validation-error";
        return false;
    } else {
        msg.innerHTML = ""
        input.className = "text-box single-line";
        return true;
    }
}

function clear(span) {
    span.innerHTML = "";
}

function checkAll() {
    var c1 = checkTitle();
    var c2 = checkReleaseDate();
    var c3 = checkGenre();
    var c4 = checkPrice();
    var c5 = checkRating();
    return c1 && c2 && c3 && c4 && c5;
}