<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ include file="/jsp/base/taglib.jsp" %>





	<table class="table table-bordered" id="file_list_table">
	
		<tr class="active">
			<th> 文件列表 </th>
		</tr>
		
		
		
		<s:iterator value="file_path_list" var="i" status="index" >  


			<tr class="success" >
				<td>  
					 <a href="<s:property value="#i.filePath"/> "> 
<%-- 						<s:property value="#i.filePath.split('/')"/> --%>
						<s:property value="@util.Util@getFileNameFromPath(#i.filePath)"/>
					 </a>  
				</td>

			</tr>
		</s:iterator>  
		
		
		

	</table>
