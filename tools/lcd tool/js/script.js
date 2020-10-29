
var pagecount = 1;

var row_idex = 1;



var rowdata1 = `<tr class="row`
var rowdata2=`"><td style="width: 100px;"><span>Row Data : </span><input style="width: 100px;" class="rowdata" maxlength="14" type= "text"/><td>
			<td style="width: 100px;">
			<span>Data Type: </span>
			<select style="width: 100px;" class="datatype">
			<option value="p1">DATA</option>
			<option value="p2">DATA WITH VARIABLE</option>
			<option value="p3">DATA WITH INPUT</option>
			<option value="p4">DATA WITH LINK</option>
			</select>
			<td>
			<td style="width: 100px;"><span>In/Var init : </span><input style="width: 100px;" type="number" disabled='disabled' maxlength="4"/><td>
			<td style="width: 100px;"><span>Next Page : <input disabled="disabled" style="width: 100px;" class="pagelink" type= "text"/><td>
			<td><button type="button" class="btn btn-danger remove" >remove</button></td>
		 </tr>`;
		 
		 
		 
var pagedata1=`<div class="draggable-parent border border-light" id="draggable-parent-2" style="max-width: 900px;display:inline-block">
<div  id="`;

var pagedata2=`" class="card bg-light mb-3 cont" style="max-width: auto;">
  <div class="card-header"> <span class="header">`;
  
var pagedata3=`</span>
  <button type="button" class="btn close" style="padding:0px; float:right;">x</button>
  <input type= "text" value="
  `
 var pagedata4=` " class="pstr_prev_page" disabled style="float:right;margin-right: 10px;"/>`
 var pagedata5 =` </div>
  <div class="card-body">
	<div class="card">
	<p><span>time out : </span><input  class="time_out" type="number" maxlength="4"/><span> x 100ms</span></p>
	<button type="button" class="btn btn-light addrow">+</button>
	<table class="datatable">
		 <tr class="row`
var pagedata6	=`"><td style="width: 100px;"><span>Row Data : </span><input style="width: 100px;" class="rowdata" maxlength="14" type= "text"/><td>
			<td style="width: 100px;">
			<span>Data Type: </span>
			<select style="width: 100px;" class="datatype">
			<option value="p1">DATA</option>
			<option value="p2">DATA WITH VARIABLE</option>
			<option value="p3">DATA WITH INPUT</option>
			<option value="p4">DATA WITH LINK</option>
			</select>
			<td>
			<td style="width: 100px;"><span>In/Var init : </span><input style="width: 100px;" type="number" disabled='disabled' maxlength="4"/><td>
			<td style="width: 100px;"><span>Next Page : <input disabled="disabled" style="width: 100px;" class="pagelink" type= "text"/><td>
			<td><button type="button" class="btn btn-danger remove" >remove</button></td>
		 </tr>
	</table>
	</div>
  </div>
  <input type="hidden" class="pastr_row_data" value="{&row`
var pagedata7=  `}" />
  <input type="hidden" class="pagename" value="`
var pagedata8= `" />
  <input type="hidden" class="u8_rows_num" value="1" />
  <input type="hidden" class="u16_time_out" value="0" />
  <input type="hidden" class="pstr_prev_page" value="`
var pagedata9=`" />
</div>
</div>`		 

	
				
$('document').ready(function(){
	
	$( "#ID0" ).draggable();
	
	
	$(document).on('click','.remove', function(){
	//	$(this).parent().parent().remove();
		alert("cannot remove Sorry refresh and take care changes not saved");
	});
	
	$(document).on('click','.close', function(){
		if($(this).parent().find('.header').html()!="Default Screen")
		{
			alert("cannot closed Sorry refresh and take care changes not saved");
		}	
	});
	$(document).on('click','.addrow', function(){
		row_idex++;
		$(this).parent().find('.datatable').append(rowdata1+row_idex.toString()+rowdata2);
		$(this).parent().parent().parent().find(".pastr_row_data").val($(this).parent().parent().parent().find(".pastr_row_data").val().slice(0,-1)+",&row"+row_idex.toString()+"}");
		$(this).parent().parent().parent().find(".u8_rows_num").val((($(this).parent().parent().parent().find(".pastr_row_data").val().match(/,/g) || []).length+1));
	});
	$(document).on('change','.datatype',function(){
		if($(this).val() == 'p1')
		{
			$(this).parent().parent().find('.rowdata').attr("maxlength","14");
			$(this).parent().parent().find("input[type=number]").attr('disabled', 'disabled');
		}
		else if($(this).val() == 'p3' || $(this).val() == 'p2')
		{
			$(this).parent().parent().find('.rowdata').attr("maxlength","10");
			if($(this).parent().parent().find('.rowdata').val().length > 10)
			{
				$(this).parent().parent().find('.rowdata').val($(this).parent().parent().find('.rowdata').val().slice(0,-4));
			}
			$(this).parent().parent().find("input[type=number]").removeAttr('disabled');
		}
		if($(this).val() == 'p4')
		{
			$(this).attr('disabled', 'disabled');
			pagecount++;
			row_idex++;
			$('body').append(pagedata1+"ID"+pagecount.toString()+pagedata2+"Page"
			+pagecount.toString()+pagedata3+$(this).parent().parent().parent().parent().parent().parent().parent().find('.header').html()+
			pagedata4+"<input type='hidden' id='INFO' class='PAGE"+
			$(this).parent().parent().parent().parent().parent().parent().parent().attr("id").replace("ID",'')+
			"'/>"+pagedata5+row_idex.toString()+pagedata6+row_idex.toString()+
			pagedata7+"Page"+pagecount.toString()+pagedata8+$(this).parent().parent().parent().parent().parent().parent().parent().find('.header').html()+pagedata9).find("#ID"+pagecount.toString()).draggable();
			$(this).parent().parent().find('.pagelink').val("Page"+pagecount.toString());
		}
	});
	 
	 $(document).on('change','.time_out',function(){
		 $(this).parent().parent().parent().parent().parent().find('.u16_time_out').val($(this).val());
	 });
	 
	 
	$(document).on('click' ,'.generate' ,function(){ 
	$('code').html(`<p>
/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "lcd_profile.h"
#include "lcd_mngr.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
</p>`);
	var id = 0;
	var prerow = "";
	var prepages = [];
	var lcd_init = "";
	$('tr').each(function () {
	id++;
	var dataType;
	if(prerow != $(this).parent().parent().parent().parent().parent().attr('id'))
	{
		id=0;
		prerow = $(this).parent().parent().parent().parent().parent().attr('id');
	}
	if($(this).find('.datatype').val()=="p1")
	{
		dataType="DATA"
	}
	else if($(this).find('.datatype').val()=="p2")
	{
		dataType="DATA_WITH_INPUT"
	}
	else if($(this).find('.datatype').val()=="p3")
	{
		dataType="DATA_WITH_VARIABLE"
	}
	else if($(this).find('.datatype').val()=="p4")
	{
		dataType="DATA_WITH_LINK"
	}
	
	
	
		row = `<p>tstr_row_data `+$(this).attr('class') +` = {
.u8_id = `+id.toString()+`,
.au8_data="`+$(this).find('.rowdata').val()+`",
.enu_data_type = `+dataType+`,
.u16_var_data = `+($(this).find('input[type=number]').val()==""?0:$(this).find('input[type=number]').val())+`,
.pstr_next_page = NULL,
};
</p>`;
		$('code').html($('code').html()+row);
		if($(this).find('.pagelink').val() !="")
		{
			prepages.push($(this).attr('class')+".pstr_next_page = "+("&"+$(this).find('.pagelink').val())+";");
		}
		
	});

	
	$('.cont').each(function () {
		page=`<p>
const tstr_row_data * a_`+$(this).find('.pagename').val()+`_rows[]= `+$(this).find('.pastr_row_data').val()+`;

tstr_lcd_mangr_inst `+$(this).find('.pagename').val()+` = {
.pastr_row_data = a_`+$(this).find('.pagename').val()+`_rows,
.u8_rows_num = `+$(this).find('.u8_rows_num').val()+`,
.u8_row_idx = 0,
.u16_time_out = `+$(this).find('.u16_time_out').val()+`,
.pstr_prev_page = `+($(this).find('.pstr_prev_page').val()!="NULL"?("&"+$(this).find('.pstr_prev_page').val()):$(this).find('.pstr_prev_page').val())+`,
};
</p>`;
		$('code').html($('code').html()+page);
	});
	
	
$('code').html($('code').html()+`<p>

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/



</p>
`);
lcd_init =`<p>void lcd_profile_init(void){
`;
		jQuery.each( prepages, function( i, val ) 
		{
			lcd_init = lcd_init+ "	"+val+`
`;
		});
	lcd_init = lcd_init + `	lcd_mangr_init(&page1);`;	
	lcd_init = lcd_init+ `
}
</p>`;

$('code').html($('code').html()+lcd_init);
$('code').html($('code').html()+`<p>void lcd_profile_dispatch(void)
{
	lcd_mangr_dispatch();
}
</p>`);
	});
 
});
  
