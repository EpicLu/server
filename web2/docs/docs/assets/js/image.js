//跳转对应图片的post页面
$(function () {
    $(".card").click(function () {

        $("#big-img").attr("src", $(this.getElementsByClassName("card-img")).attr("src"));//设置#big-img元素的src属性

        $("#enlarge-div").fadeIn("fast");//显示弹出层

        $("#enlarge-div").click(function () {//关闭弹出层
            $(this).fadeOut("fast");
        });
    });
});
//点击放大图片
function goPost(id){
    const image = document.getElementById(`post-image${id}`);
    const title = document.getElementById(`post-title${id}`);

    const src = image.src;
    const text = title.textContent;
    
    const query = `?post-image=${src}&post-title=${text}`;

    location.search = query;
    location.href = `post.html${query}`;
}

$( document ).ready(function() {
   
});