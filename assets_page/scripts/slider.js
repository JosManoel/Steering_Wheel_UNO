image_slide = document.getElementById("imageSlide");
var index_image = 0;
var sliderInterval;
var image_list = [
    '/assets_page/images/Image4.png', 
    '/assets_page/images/Image5.png', 
    '/assets_page/images/Image6.png'
];

function changeImage(image, array_image, index){
    
    image.src = array_image[index];
}

function indexImage(index){
    

    if(index !== 'undefined'){
        if(index_image == (image_list.length - 1)){
            index_image = 0;
        }else{
            index_image++;
        }
    }else{
        index_image = index;
    }
    changeImage(image_slide, image_list, index_image);
    return index_image;
}

function backImage(){    
    clearInterval(sliderInterval);
    indexImage(indexImage - 1, image_list);
    start();
}

function nextImage(){
    clearInterval(sliderInterval);
    indexImage(indexImage + 1, image_list);
    start();
}

function start(){
    
    sliderInterval = setInterval(() => {
        indexImage();
    },5000)
}

window.addEventListener("load",start);

