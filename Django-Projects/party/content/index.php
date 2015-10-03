<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="Party Information">
    <meta name="author" content="David">

    <title>党务工作指导系统</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/grayscale.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link href="http://fonts.googleapis.com/css?family=Lora:400,700,400italic,700italic" rel="stylesheet" type="text/css">
    <link href="http://fonts.googleapis.com/css?family=Montserrat:400,700" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body id="page-top" data-spy="scroll" data-target=".navbar-fixed-top" style="color:b80000;">



    <!-- Navigation -->
    <nav class="navbar navbar-custom navbar-fixed-top" role="navigation">
        <div class="container">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-main-collapse">
                    <i class="fa fa-bars"></i>
                </button>
                <a class="navbar-brand page-scroll" href="#page-top">
                    <i class="fa fa-play-circle"></i>  回到顶部
                </a>
            </div>

            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse navbar-right navbar-main-collapse">
                <ul class="nav navbar-nav">
                    <!-- Hidden li included to remove active class from about link when scrolled up past about section -->
                    <li class="hidden">
                        <a href="#page-top"></a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#news">最新通知</a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#file">文件查询</a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#contact">联系我们</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container -->
    </nav>

    <!-- Intro Header -->
    <header class="intro">
        <div class="intro-body">
            <div class="container">
                <div class="row">
                    <div class="col-md-8 col-md-offset-2">
                        <h1 class="brand-heading">党务工作指导系统</h1>
                        <p class="intro-text">电子信息与电气工程学部学生工作办公室党支部</p>
                        <a href="#news" class="btn btn-circle page-scroll">
                            <i class="fa fa-angle-double-down animated"></i>
                        </a>
                    </div>
                </div>
            </div>
        </div>
    </header>

    <section id="news" class="container content-section text-center">
            <div class="col-lg-8 col-lg-offset-2">
                <h2>最新党务通知</h2>
				
				<table class="table">
				<tr>
					<th>序号</th>
					<th>通知标题</th>
					<th>发布时间</th>
					<th>详细</th>
				</tr>
				  <?php
					DEFINE ('DB_USER', 'root');
					DEFINE ('DB_PASSWORD', 'root');
					DEFINE ('DB_HOST', 'localhost:3306');
					DEFINE ('DB_NAME', 'test');
					$dbc = mysqli_connect (DB_HOST, DB_USER, DB_PASSWORD);
					mysqli_select_db($dbc,DB_NAME);
					$query="select * from news";
					$result=mysqli_query($dbc,$query);
					$titleset=false;
					while($ans=mysqli_fetch_array($result,MYSQL_ASSOC))
					{
						echo  "<tr href='#'>\n";
						foreach($ans as $key=>$value)
						{	
							if($key=='id')
							{
								$id=$value;
							}
							else if($key=='title')
							{
								$title=$value;
							}
							else if($key=='time')
							{
								$time=$value;
							}
							else if($key=='content')
							{
								echo "<div class=\"modal fade\"  id=\"newsdata-$id\" tabindex=\"-1\" role=\"dialog\" aria-labelledby=\"myModalLabel\" aria-hidden=\"true\">";
								echo '
									<div class="modal-dialog" style="width:1000px;">
										<div class="modal-content">
											 <div class="modal-header">
												<button type="button" class="close"
												   data-dismiss="modal" aria-hidden="true">
													  &times;
												</button>
												<h4 class="modal-title" id="myModalLabel" style="color:#000;">';
												   echo $title;
												   echo '
												</h4>
											 </div>
											 <div class="modal-body" style=\"width:900px;\">';
												echo $value;
												echo '
											 </div>
											 <div class="modal-footer">
												<button type="button" class="btn btn-default btn-info"
												   data-dismiss="modal">确定
												</button>
											 </div>
										</div>
									</div>
								</div>';
								break;
							};
							echo "<td>".$value."</td>";
							echo "\n";
						}
						echo "<td><button class=\"btn btn-default btn-info\"  href=\"#newsdata-$id\" data-toggle=\"modal\" type=\"button\">查看</button></td>";
						echo "</tr>";
						
					}
					
				  ?>
				</table>
            </div>
        </div>
    </section>

    <section id="file" class="content-section text-center">
        <div class="download-section">
            <div class="container">
                <div class="col-lg-8 col-lg-offset-2">
                    <h2>党务工作文件列表</h2>
					<table class="table">
					<tr>
						<th>序号</th>
						<th>文件名</th>
						<th>地址</th>
						<th>在线阅读</th>
						<th>下载链接</th>
					</tr>
                    <?php
					$query="select * from files;";
					$result=mysqli_query($dbc,$query);
					$titleset=false;
					while($ans=mysqli_fetch_array($result,MYSQL_ASSOC))
					{
						echo  "<tr href='#'>\n";
						foreach($ans as $key=>$value)
						{	
							echo "<td>".$value."</td>";
							echo "\n";
							if($key=='path')
								$path=$value;
						}
						echo "<td><a href=\"web\pdfviewer.html?file=".$path."\">阅读</a></td>";
						echo "<td><a href=\"pdfcontents\\".$path."\">下载</a></td>";
						echo "</tr>";						
					}
					?>
					</table>
                </div>
            </div>
        </div>
    </section>

    <section id="contact" class="container content-section text-center">
        <div class="row">
            <div class="col-lg-8 col-lg-offset-2">
                <h2>联系学生工作办公室党支部</h2>
                <p>辽宁省大连市大连理工大学创新园大厦B座311</p>
                <p>邮箱:<a href="mailto:feedback@startbootstrap.com">mail@mail.com</a>
                </p>
            </div>
        </div>
    </section>


    <!-- Footer -->
    <footer>
        <div class="container text-center">
            <p>Copyright &copy; Time1ess 2015</p>
        </div>
    </footer>
    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <!-- Plugin JavaScript -->
    <script src="js/jquery.easing.min.js"></script>
	
    <!-- Custom Theme JavaScript -->
    <script src="js/grayscale.js"></script>

</body>

</html>
