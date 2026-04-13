/*
==================================================
  Royal Window Cleaning Website
  © 2026 Royal Window Cleaning, Inc. All Rights Reserved
  Website by Thomas Hoerger
==================================================
*/


// ======================================================
// FADE ANIMATION
// ======================================================

const observer = new IntersectionObserver(entries=>{
entries.forEach(entry=>{
if(entry.isIntersecting){
entry.target.classList.add("show");
}
});
});

document.querySelectorAll(".fade").forEach(el=>{
observer.observe(el);
});


// ======================================================
// LIGHTBOX FUNCTIONALITY
// ======================================================

const lightbox = document.getElementById("lightbox");
const lightboxImg = document.getElementById("lightbox-img");

if(lightbox){
document.querySelectorAll(".zoomable").forEach(img=>{
img.addEventListener("click",()=>{
lightbox.style.display="flex";
lightboxImg.src=img.src;
});
});

lightbox.addEventListener("click",()=>{
lightbox.style.display="none";
});
}


// ======================================================
// MOBILE NAVIGATION MENU
// ======================================================

const toggle = document.querySelector(".menu-toggle");
const nav = document.querySelector(".main-nav");

if(toggle && nav){
toggle.addEventListener("click", ()=>{
nav.classList.toggle("active");
});
}


// ======================================================
// CONTACT FORM VALIDATION
// ======================================================

const form = document.querySelector(".contact-form");

if(form){
form.addEventListener("submit", function(e){

const services = document.querySelectorAll('input[name="Services[]"]:checked');

if(services.length === 0){
alert("Please select at least one service.");
e.preventDefault();
}

});
}


// ======================================================
// HOMEPAGE IMAGE SLIDER
// ======================================================

const slide = document.getElementById("work-slide");

if(slide){

const images = [
"./assets/images/window-cleaning-example-2.JPEG",
"./assets/images/pressure-wash-example-1.jpg",
"./assets/images/window-cleaning-example-1.JPEG",
"./assets/images/010.JPEG",
"./assets/images/005.JPEG",
"./assets/images/window-cleaning-example-9.JPEG"
];

let index = 0;

const dotsContainer = document.querySelector(".slider-dots");
const nextBtn = document.querySelector(".next");
const prevBtn = document.querySelector(".prev");


// CREATE DOTS
images.forEach((_,i)=>{
const dot=document.createElement("span");
dot.onclick=()=>showSlide(i);
dotsContainer.appendChild(dot);
});

const dots = dotsContainer.querySelectorAll("span");


function showSlide(i){

index=i;
slide.src=images[index];

dots.forEach(d=>d.classList.remove("active"));
dots[index].classList.add("active");

}


// ARROWS

if(nextBtn){
nextBtn.onclick=()=>{
index=(index+1)%images.length;
showSlide(index);
};
}

if(prevBtn){
prevBtn.onclick=()=>{
index=(index-1+images.length)%images.length;
showSlide(index);
};
}


// MOBILE SWIPE

let startX=0;

slide.addEventListener("touchstart",e=>{
startX=e.touches[0].clientX;
});

slide.addEventListener("touchend",e=>{
let endX=e.changedTouches[0].clientX;

if(startX-endX>50){
index=(index+1)%images.length;
}

if(endX-startX>50){
index=(index-1+images.length)%images.length;
}

showSlide(index);

});

showSlide(0);

}


// ======================================================
// GUTTER IMAGE SLIDER
// ======================================================

const gutterSlide = document.getElementById("gutter-slide");

if(gutterSlide){

const gutterImages=[
"./assets/images/022.JPEG",
"./assets/images/021.JPEG",
"./assets/images/005.JPEG",
"./assets/images/006.JPEG"
];

let gutterIndex=0;

const gutterNext=document.querySelector(".gutter-next");
const gutterPrev=document.querySelector(".gutter-prev");


// DOTS

const gutterDotsContainer=document.createElement("div");
gutterDotsContainer.className="slider-dots";

gutterSlide.parentElement.appendChild(gutterDotsContainer);

gutterImages.forEach((_,i)=>{
const dot=document.createElement("span");
dot.onclick=()=>showGutterSlide(i);
gutterDotsContainer.appendChild(dot);
});

const gutterDots=gutterDotsContainer.querySelectorAll("span");


function showGutterSlide(i){

gutterIndex=i;
gutterSlide.src=gutterImages[gutterIndex];

gutterDots.forEach(d=>d.classList.remove("active"));
gutterDots[gutterIndex].classList.add("active");

}


// ARROWS

if(gutterNext){
gutterNext.onclick=()=>{
gutterIndex=(gutterIndex+1)%gutterImages.length;
showGutterSlide(gutterIndex);
};
}

if(gutterPrev){
gutterPrev.onclick=()=>{
gutterIndex=(gutterIndex-1+gutterImages.length)%gutterImages.length;
showGutterSlide(gutterIndex);
};
}


// MOBILE SWIPE

let gutterStartX=0;

gutterSlide.addEventListener("touchstart",e=>{
gutterStartX=e.touches[0].clientX;
});

gutterSlide.addEventListener("touchend",e=>{

let gutterEndX=e.changedTouches[0].clientX;

if(gutterStartX-gutterEndX>50){
gutterIndex=(gutterIndex+1)%gutterImages.length;
}

if(gutterEndX-gutterStartX>50){
gutterIndex=(gutterIndex-1+gutterImages.length)%gutterImages.length;
}

showGutterSlide(gutterIndex);

});

showGutterSlide(0);

}


// ======================================================
// WINDOW IMAGE SLIDER
// ======================================================

const windowSlide = document.getElementById("window-slide");

if(windowSlide){

const windowImages=[
"./assets/images/window-cleaning-example-5.JPEG",
"./assets/images/window-cleaning-example-4.JPEG",
"./assets/images/window-cleaning-example-3.JPEG",
"./assets/images/window-cleaning-example-8.JPEG",
"./assets/images/window-cleaning-example-7.JPEG"
];

let windowIndex=0;

const windowNext=document.querySelector(".gutter-next");
const windowPrev=document.querySelector(".gutter-prev");


// DOTS

const windowDotsContainer=document.createElement("div");
windowDotsContainer.className="slider-dots";

windowSlide.parentElement.appendChild(windowDotsContainer);

windowImages.forEach((_,i)=>{
const dot=document.createElement("span");
dot.onclick=()=>showWindowSlide(i);
windowDotsContainer.appendChild(dot);
});

const windowDots=windowDotsContainer.querySelectorAll("span");


function showWindowSlide(i){

windowIndex=i;
windowSlide.src=windowImages[windowIndex];

windowDots.forEach(d=>d.classList.remove("active"));
windowDots[windowIndex].classList.add("active");

}


// ARROWS

if(windowNext){
windowNext.onclick=()=>{
windowIndex=(windowIndex+1)%windowImages.length;
showWindowSlide(windowIndex);
};
}

if(windowPrev){
windowPrev.onclick=()=>{
windowIndex=(windowIndex-1+windowImages.length)%windowImages.length;
showWindowSlide(windowIndex);
};
}


// MOBILE SWIPE

let windowStartX=0;

windowSlide.addEventListener("touchstart",e=>{
windowStartX=e.touches[0].clientX;
});

windowSlide.addEventListener("touchend",e=>{

let windowEndX=e.changedTouches[0].clientX;

if(windowStartX-windowEndX>50){
windowIndex=(windowIndex+1)%windowImages.length;
}

if(windowEndX-windowStartX>50){
windowIndex=(windowIndex-1+windowImages.length)%windowImages.length;
}

showWindowSlide(windowIndex);

});

showWindowSlide(0);

}


// ======================================================
// BLIND IMAGE SLIDER
// ======================================================

const blindSlide = document.getElementById("blind-slide");

if(blindSlide){

const blindImages=[
"./assets/images/blind-example-5.JPEG",
"./assets/images/blind-example-1.JPEG",
"./assets/images/blind-example-2.JPEG",
"./assets/images/blind-example-3.JPEG",
"./assets/images/blind-example-4.JPEG"
];

let blindIndex=0;

const blindNext=document.querySelector(".gutter-next");
const blindPrev=document.querySelector(".gutter-prev");


// DOTS

const blindDotsContainer=document.createElement("div");
blindDotsContainer.className="slider-dots";

blindSlide.parentElement.appendChild(blindDotsContainer);

blindImages.forEach((_,i)=>{
const dot=document.createElement("span");
dot.onclick=()=>showBlindSlide(i);
blindDotsContainer.appendChild(dot);
});

const blindDots=blindDotsContainer.querySelectorAll("span");


function showBlindSlide(i){

blindIndex=i;
blindSlide.src=blindImages[blindIndex];

blindDots.forEach(d=>d.classList.remove("active"));
blindDots[blindIndex].classList.add("active");

}


// ARROWS

if(blindNext){
blindNext.onclick=()=>{
blindIndex=(blindIndex+1)%blindImages.length;
showBlindSlide(blindIndex);
};
}

if(blindPrev){
blindPrev.onclick=()=>{
blindIndex=(blindIndex-1+blindImages.length)%blindImages.length;
showBlindSlide(blindIndex);
};
}


// MOBILE SWIPE

let blindStartX=0;

blindSlide.addEventListener("touchstart",e=>{
blindStartX=e.touches[0].clientX;
});

blindSlide.addEventListener("touchend",e=>{

let blindEndX=e.changedTouches[0].clientX;

if(blindStartX-blindEndX>50){
blindIndex=(blindIndex+1)%blindImages.length;
}

if(blindEndX-blindStartX>50){
blindIndex=(blindIndex-1+blindImages.length)%blindImages.length;
}

showBlindSlide(blindIndex);

});

showBlindSlide(0);

}