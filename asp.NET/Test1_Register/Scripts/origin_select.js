$(function () {
    var beijing = ["北京"];
    var shandong = ["济南", "青岛", "临沂"];
    var sichuan = ["成都", "重庆"];
    var guangdong = ["广州", "深圳", "佛山"];
    var jiangsu = ["南京", "徐州", "扬州"];
    
    $("#select_province").change(function () {
        var region = $("#select_region");
        region.empty();
        var selected = $(this).val();
        switch (selected) {
            case "北京":
                for (var i = 0; i < beijing.length; ++i) {
                    var option = $("<option>").val(beijing[i]).text(beijing[i]);

                    region.append(option);
                }
                break;
            case "山东":
                for (var i = 0; i < shandong.length; ++i) {
                    var option = $("<option>").val(shandong[i]).text(shandong[i]);
                    region.append(option);
                }
                break;
            case "四川":
                for (var i = 0; i < sichuan.length; ++i) {
                    var option = $("<option>").val(sichuan[i]).text(sichuan[i]);
                    region.append(option);
                }
                break;
            case "广东":
                for (var i = 0; i < guangdong.length; ++i) {
                    var option = $("<option>").val(guangdong[i]).text(guangdong[i]);
                    region.append(option);
                }
                break;
            case "江苏":
                for (var i = 0; i < jiangsu.length; ++i) {
                    var option = $("<option>").val(jiangsu[i]).text(jiangsu[i]);
                    region.append(option);
                }
                break;
        }
    });
});