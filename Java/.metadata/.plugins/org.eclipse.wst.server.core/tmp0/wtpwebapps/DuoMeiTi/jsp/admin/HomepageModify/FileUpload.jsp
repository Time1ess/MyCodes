<%@ include file="/jsp/base/taglib.jsp" %>

<layout:override name="mycontent">
	
	
	<form method="post" action="" enctype="multipart/form-data">	
		<br/>
		<input type="file" id="file_upload">
		
		<br/>
		<button class="btn btn-primary" id="file_upload_button" type="button" > 上传</button>
	</form>
	
	<div id="ClassroomFileTableDiv">
		<%@ include file="/jsp/admin/HomepageModify/ClassroomFileTable.jsp" %>
	</div>
	

<script> 
	
	
	$(document).on("click", "#file_upload_button", function() {
		
		var fd = new FormData();

     	fd.append("file", document.getElementById('file_upload').files[0]); 
     	
//      	fd.append("test", "YESYESYES");
 
	    $.ajax({  
	          url: "HomepageModify/FileUploadInsert" ,  
	          type: "POST",  
	          data: fd,  
	          async: true,  
	          cache: false,  
	          contentType: false,  
	          processData: false,  
	          success: insertCallBack,
// 	          {
// 	        	  alert("GOOD");
// 	        	  window.location.reload() 
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
	
	function insertCallBack(data)
	{
// 		alert("GOGO");
// 		alert(data.classroom_file_table);
		$(document).find("#ClassroomFileTableDiv").html(data.classroom_file_table)
// 		window.location.reload() 
// 		$(document).find("#file_list_table tr:first").after("<td>" + data. "  </td")
// 		$("#file_list_table").tr.
// 		alert("BACK");
	}
	


</script>
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

</layout:override>

<%@ include file="/jsp/admin/HomepageModify/Base.jsp" %>
