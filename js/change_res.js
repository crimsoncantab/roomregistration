function set_vals(select_el) {
    var selected = select_el.options[select_el.selectedIndex].value;
    var myform = select_el.form;
    var dollar = selected.indexOf('$');
    myform.room.value=selected.substr(0, dollar);
    myform.building.value=selected.substr(dollar+1);
}