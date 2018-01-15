function Click(ob){
 var o = ob.nextSibling;
 while(o.nodeType!=1) o=o.nextSibling;
 if(o.style.display!="block"){o.style.display="block";ob.style.cursor="pointer";}else{o.style.display="none";ob.style.cursor="help";}
}
function OpenNext(ob){
 var o = ob.nextSibling;
 while(o.nodeType!=1) o=o.nextSibling;
 Open(o);
}
function OpenPrev(ob){
 var o = ob.previousSibling;
 while(o.nodeType!=1) o=o.previousSibling;
 Open(o);
}
function Open(o){
 if(window['t']==undefined || t['document']==undefined)
 t=window.open('','New','height=250,width=250,location=no,menubar=no,scrollbars=no',false);
 t.document.open();
 t.document.write(o.innerHTML);
 t.document.close();
 t.focus();
}