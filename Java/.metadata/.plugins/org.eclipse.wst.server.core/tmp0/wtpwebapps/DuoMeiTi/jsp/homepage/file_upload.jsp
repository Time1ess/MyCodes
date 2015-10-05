<%@ include file="/jsp/base/taglib.jsp" %>





<layout:override name="main_content">

<form method="post" action="/file_upload" enctype="multipart/form-data">
	
		<br/>
		<input type="file" id="file_upload">
		
		<br/>
		<button class="btn btn-primary" id="file_upload_button" type="button" > 提交</button>
</form>

	<table class="table table-bordered" id="user_table">
	
		<tr class="active">
			<th> 文件列表 </th>
		</tr>
		
		
		<s:iterator value="file_path_list" var="i" status="index" >  
			<tr class="success" >
				<td>   <a href="<s:property value="#i.filePath"/> "> <s:property value="#i.filePath"/></a>   </td>

			</tr>
		</s:iterator>  
		
		
		

	</table>


<script> 
	
	
	$(document).on("click", "#file_upload_button", function() {
		
		var fd = new FormData();

     	fd.append("image", document.getElementById('file_upload').files[0]); 
     	
     	fd.append("test", "YESYESYES");
 
	    $.ajax({  
	          url: "" ,  
	          type: "POST",  
	          data: fd,  
	          async: true,  
	          cache: false,  
	          contentType: false,  
	          processData: false,  
// 	          success: function (returndata) {  
// 	              alert(returndata);  
// 	          },  
// 	          error: function (returndata) {  
// 	              alert(returndata);  
// 	          }  
	     });  

		
		
// 		xmlhttp=new XMLHttpRequest();
// 		alert("DOUBI");
// 		xmlhttp.open("POST","",true);
// 		var fd = new FormData();

//         fd.append("image", document.getElementById('file_upload').files[0]); 
// 		xmlhttp.send(fd);

		
	})


</script>

</layout:override>














<%@ include file="/jsp/homepage/base.jsp" %>

