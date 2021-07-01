function openMenu(id,id_button,image_link1,image_link2){ 
    let menu = document.getElementById(id);
    var button = document.getElementById(id_button);

    if(menu.style.display !== 'flex'){
        menu.style.display = ('flex');
        button.setAttribute('src',image_link1);
        
        
    }else{
        menu.style.display = ('none');
        button.setAttribute('src',image_link2);
    }
}
