var ck_version = false;
var linkGerber = "https://github.com/JosManoel/Steering_Wheel_UNO/raw/main/Gerber/Gerber_Steering_Wheel_UNO.zip";


function swapText(id, new_text){
    document.getElementById(id).innerHTML = new_text;
}

function swapImage(id, new_src){
    document.getElementById(id).src = new_src;
}

function openPage(link){
    window.open(link, 'blank');
}

function openProfile(){
    openPage("https://github.com/JosManoel");
}

function openRepo(){
    openPage("https://github.com/JosManoel/Steering_Wheel_UNO");
}

function donwloadPDF(){
    openPage("https://github.com/JosManoel/Steering_Wheel_UNO/raw/main/Schematic/Steering_Wheel_UNO.pdf");
}

function donwloadEsq(){
    openPage("https://github.com/JosManoel/Steering_Wheel_UNO/raw/main/Schematic/Schematic_PDF.pdf");
}

function donwloadGerber(){
    openPage(linkGerber);
}

function alt_version(){
    if(ck_version === false){
        swapImage("home_image", "assets/PCB_home_alt.png");
        swapImage("bottom_image", "assets/PCB_Bottom_alt.png");
        swapImage("top_image", "assets/PCB_Top_alt.png");

        swapText("version_text", "Versão: Hibica 1.2");
        swapText("note", "Versão criada em homenagem ao Grupo Para Pessoas Pobres com Computadores Ruins, presente no Facebook.");

        linkGerber = "https://github.com/JosManoel/Steering_Wheel_UNO/raw/main/Gerber/Grupo_para_pessoas_pobres_com_computadores_ruins.zip";    
    }

    if(ck_version === true){
        swapImage("home_image", "assets/PCB_home.png");
        swapImage("bottom_image", "assets/PCB_Bottom.png");
        swapImage("top_image", "assets/PCB_Top.png");

        swapText("version_text", "Versão: 1.2");
        swapText("note", "");
        
        linkGerber = "https://github.com/JosManoel/Steering_Wheel_UNO/raw/main/Gerber/Gerber_Steering_Wheel_UNO.zip";
    }

    ck_version = !ck_version;
}
