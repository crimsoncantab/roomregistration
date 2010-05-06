function pop_sub_form(i, room, building) {
    var select_el = document.getElementById('time'+i);
    var selected = select_el.options[select_el.selectedIndex].value;
    var dollar = selected.indexOf('$');
    var myform = document.handle_req;

    myform.start_time.value=selected.substr(0, dollar);
    myform.end_time.value=selected.substr(dollar+1);
    myform.room.value = room;
    myform.building.value = building;

    myform.submit();

}