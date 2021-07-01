function setId(index, elements){
    elements[index].id = (elements[index].innerHTML).trim().replace(/\s+/g, '_');
    
    return elements[index].id;
}

function setClass( index, elements, summaryElement){
    if ((elements[index]).className == "title"){
        summaryElement.className = "summaryTitle";
    }else{
        summaryElement.className = "summarySubtitle";
    }
}

function createElement (summary, elements, index){
    var titleSummaryElement = document.createElement("a");

    setClass(index, elements, titleSummaryElement);
    titleSummaryElement.setAttribute("href","#" + setId(index,elements));
    titleSummaryElement.appendChild(document.createTextNode(elements[index].innerHTML));

    summary.appendChild(titleSummaryElement);
}

function getSumario(){
    var elements = document.querySelectorAll(".article h2");
    var summary = document.querySelector(".index");

    for (var i = 0; i < elements.length; i++){
        createElement(summary,elements,i); 
    }
}

window.addEventListener("load",getSumario);
