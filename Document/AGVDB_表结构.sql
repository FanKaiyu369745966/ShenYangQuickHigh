USE [master]
GO
/****** Object:  Database [AGVDB]    Script Date: 2019/12/12 18:46:49 ******/
CREATE DATABASE [AGVDB]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'AGVDB', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\AGVDB.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'AGVDB_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\AGVDB_log.ldf' , SIZE = 73728KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
ALTER DATABASE [AGVDB] SET COMPATIBILITY_LEVEL = 140
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [AGVDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [AGVDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [AGVDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [AGVDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [AGVDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [AGVDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [AGVDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [AGVDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [AGVDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [AGVDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [AGVDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [AGVDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [AGVDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [AGVDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [AGVDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [AGVDB] SET  DISABLE_BROKER 
GO
ALTER DATABASE [AGVDB] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [AGVDB] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [AGVDB] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [AGVDB] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [AGVDB] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [AGVDB] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [AGVDB] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [AGVDB] SET RECOVERY FULL 
GO
ALTER DATABASE [AGVDB] SET  MULTI_USER 
GO
ALTER DATABASE [AGVDB] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [AGVDB] SET DB_CHAINING OFF 
GO
ALTER DATABASE [AGVDB] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [AGVDB] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [AGVDB] SET DELAYED_DURABILITY = DISABLED 
GO
EXEC sys.sp_db_vardecimal_storage_format N'AGVDB', N'ON'
GO
ALTER DATABASE [AGVDB] SET QUERY_STORE = OFF
GO
USE [AGVDB]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_ABNORMAL]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_ABNORMAL](
	[abnormal_id] [int] IDENTITY(1,1) NOT NULL,
	[abnormal_time] [datetime] NOT NULL,
	[abnormal_source] [nvarchar](50) NOT NULL,
	[abnormal_desc] [nvarchar](50) NOT NULL,
	[abnormal_level] [int] NOT NULL,
	[abnormal_state] [int] NOT NULL,
 CONSTRAINT [PK_AGVDB_INFO_ABNORMAL] PRIMARY KEY CLUSTERED 
(
	[abnormal_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_AGV]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_AGV](
	[agv_id] [int] NOT NULL,
	[agv_type] [nvarchar](50) NOT NULL,
	[agv_client] [int] NOT NULL,
	[agv_ip] [nvarchar](50) NOT NULL,
	[agv_port] [int] NOT NULL,
	[agv_locol_ip] [nvarchar](50) NULL,
	[agv_locol_port] [int] NULL,
	[agv_connection] [nvarchar](50) NULL,
	[agv_mode] [int] NULL,
	[agv_mode_info] [nvarchar](50) NULL,
	[agv_cur] [int] NULL,
	[agv_target] [int] NULL,
	[agv_status] [int] NULL,
	[agv_status_info] [nvarchar](50) NULL,
	[agv_battery] [int] NULL,
	[agv_speed] [int] NULL,
	[agv_speed_info] [float] NULL,
	[agv_cargo] [int] NULL,
	[agv_cargo_info] [nvarchar](50) NULL,
	[agv_action] [int] NULL,
	[agv_action_status] [int] NULL,
	[agv_action_time] [int] NULL,
	[agv_action_info] [nvarchar](50) NULL,
	[agv_error] [int] NULL,
	[agv_error_info] [nvarchar](50) NULL,
 CONSTRAINT [PK_AGV] PRIMARY KEY CLUSTERED 
(
	[agv_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_AGVTYPE]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_AGVTYPE](
	[type_name] [nvarchar](50) NOT NULL,
	[type_brand] [nvarchar](50) NULL,
	[type_version] [nvarchar](50) NULL,
	[type_max_speed] [float] NOT NULL,
	[type_max_weight] [float] NULL,
	[type_protocol] [int] NOT NULL,
	[type_action] [text] NOT NULL,
 CONSTRAINT [PK_AGVDB_INFO_AGVTYPE] PRIMARY KEY CLUSTERED 
(
	[type_name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_BACKGROUND]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_BACKGROUND](
	[bg_scal] [float] NULL,
	[bg_offset_x] [int] NULL,
	[bg_offset_y] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_CALLER]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_CALLER](
	[caller_id] [int] NOT NULL,
	[caller_address] [nvarchar](50) NULL,
	[caller_bind_station] [int] NOT NULL,
	[caller_enable] [int] NOT NULL,
	[caller_scream] [int] NULL,
	[caller_scream_info] [nvarchar](50) NULL,
	[caller_call] [int] NOT NULL,
	[caller_call_info] [nvarchar](50) NULL,
	[caller_cancel] [int] NOT NULL,
	[caller_cancel_info] [nvarchar](50) NULL,
	[caller_x] [int] NULL,
	[caller_y] [int] NULL,
 CONSTRAINT [PK_AGVDB_INFO_CALLER] PRIMARY KEY CLUSTERED 
(
	[caller_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_CHARGER]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_CHARGER](
	[charger_id] [int] NOT NULL,
	[charger_location] [int] NOT NULL,
	[charger_name] [nvarchar](50) NULL,
	[charger_x] [int] NOT NULL,
	[charger_y] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_REST]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_REST](
	[rester_id] [int] NOT NULL,
	[rester_location] [int] NOT NULL,
	[rester_name] [nvarchar](50) NULL,
	[rester_lock] [text] NULL,
	[rester_x] [int] NULL,
	[rester_y] [int] NULL,
 CONSTRAINT [PK_Rest_1] PRIMARY KEY CLUSTERED 
(
	[rester_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_RESTQUEUE]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_RESTQUEUE](
	[queue_id] [int] NOT NULL,
	[queue_list] [text] NOT NULL,
 CONSTRAINT [PK_AGVDB_INFO_RESTQUEUE] PRIMARY KEY CLUSTERED 
(
	[queue_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_RFID]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_RFID](
	[rfid_id] [int] NOT NULL,
	[rfid_x] [int] NOT NULL,
	[rfid_y] [int] NOT NULL,
 CONSTRAINT [PK_Mark] PRIMARY KEY CLUSTERED 
(
	[rfid_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_TRACK]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_TRACK](
	[track_start_x] [int] NOT NULL,
	[track_start_y] [int] NOT NULL,
	[track_end_x] [int] NOT NULL,
	[track_end_y] [int] NOT NULL,
	[track_arc] [int] NOT NULL,
 CONSTRAINT [PK_Track] PRIMARY KEY CLUSTERED 
(
	[track_start_x] ASC,
	[track_start_y] ASC,
	[track_end_x] ASC,
	[track_end_y] ASC,
	[track_arc] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_TRAFFIC]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_TRAFFIC](
	[traffic_id] [int] NOT NULL,
	[traffic_lock] [text] NULL,
	[traffic_compare] [text] NULL,
 CONSTRAINT [PK_Traffic] PRIMARY KEY CLUSTERED 
(
	[traffic_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_USER]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_USER](
	[user_name] [nvarchar](50) NOT NULL,
	[user_passwd] [nvarchar](50) NOT NULL,
	[user_level] [int] NOT NULL,
 CONSTRAINT [PK_AGVDB_USER] PRIMARY KEY CLUSTERED 
(
	[user_name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_INFO_WORK]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_INFO_WORK](
	[worker_id] [int] NOT NULL,
	[worker_location] [int] NOT NULL,
	[worker_name] [nvarchar](50) NULL,
	[worker_x] [int] NULL,
	[worker_y] [int] NULL,
 CONSTRAINT [PK_Station] PRIMARY KEY CLUSTERED 
(
	[worker_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_TASK_CURRENT]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_TASK_CURRENT](
	[task_order] [nvarchar](50) NOT NULL,
	[task_id] [int] IDENTITY(1,1) NOT NULL,
	[task_tray] [nvarchar](50) NULL,
	[task_target] [nvarchar](50) NOT NULL,
	[task_mission] [nvarchar](50) NOT NULL,
	[task_executer] [int] NOT NULL,
	[task_status] [nvarchar](50) NOT NULL,
	[task_publish] [datetime] NOT NULL,
	[task_execution] [datetime] NULL,
	[task_finish] [datetime] NULL,
	[task_error] [nvarchar](200) NULL,
	[task_log] [nvarchar](200) NULL,
 CONSTRAINT [PK_AGVDB_TASK_CURRENT] PRIMARY KEY CLUSTERED 
(
	[task_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AGVDB_TASK_HISTORY]    Script Date: 2019/12/12 18:46:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AGVDB_TASK_HISTORY](
	[task_order] [nvarchar](50) NULL,
	[task_id] [int] NOT NULL,
	[task_tray] [nvarchar](50) NULL,
	[task_target] [nvarchar](50) NULL,
	[task_mission] [nvarchar](50) NULL,
	[task_executer] [int] NULL,
	[task_status] [nvarchar](50) NULL,
	[task_publish] [datetime] NULL,
	[task_execution] [datetime] NULL,
	[task_finish] [datetime] NULL,
	[task_error] [nvarchar](200) NULL,
	[task_log] [nvarchar](200) NULL
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[AGVDB_INFO_ABNORMAL] ADD  CONSTRAINT [DF_AGVDB_INFO_ABNORMAL_abnormal_time]  DEFAULT (getdate()) FOR [abnormal_time]
GO
ALTER TABLE [dbo].[AGVDB_INFO_ABNORMAL] ADD  CONSTRAINT [DF_AGVDB_INFO_ABNORMAL_abnormal_level]  DEFAULT ((1)) FOR [abnormal_level]
GO
ALTER TABLE [dbo].[AGVDB_INFO_ABNORMAL] ADD  CONSTRAINT [DF_AGVDB_INFO_ABNORMAL_abnormal_state]  DEFAULT ((1)) FOR [abnormal_state]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Port]  DEFAULT ((0)) FOR [agv_port]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_LocalPort]  DEFAULT ((0)) FOR [agv_locol_port]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_connection]  DEFAULT (N'未连接') FOR [agv_connection]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_mode]  DEFAULT ((0)) FOR [agv_mode]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_mode_info]  DEFAULT (N'手动') FOR [agv_mode_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Cur]  DEFAULT ((0)) FOR [agv_cur]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Target]  DEFAULT ((0)) FOR [agv_target]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Status]  DEFAULT ((0)) FOR [agv_status]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_status_info]  DEFAULT (N'待机') FOR [agv_status_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Battery]  DEFAULT ((0)) FOR [agv_battery]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Speed]  DEFAULT ((0)) FOR [agv_speed]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_speed_info]  DEFAULT ((0.0)) FOR [agv_speed_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Cargo]  DEFAULT ((0)) FOR [agv_cargo]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_cargo_info]  DEFAULT (N'空载') FOR [agv_cargo_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Action]  DEFAULT ((0)) FOR [agv_action]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_ActionStatus]  DEFAULT ((0)) FOR [agv_action_status]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_action_time]  DEFAULT ((0)) FOR [agv_action_time]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_action_info]  DEFAULT (N'无') FOR [agv_action_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_Error]  DEFAULT ((0)) FOR [agv_error]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGV] ADD  CONSTRAINT [DF_AGVDB_INFO_AGV_agv_error_info]  DEFAULT (N'无异常') FOR [agv_error_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_AGVTYPE] ADD  CONSTRAINT [DF_AGVDB_INFO_AGVTYPE_MaxSpeed]  DEFAULT ((0)) FOR [type_max_speed]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Station]  DEFAULT ((0)) FOR [caller_bind_station]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Enable]  DEFAULT ((0)) FOR [caller_enable]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Scream]  DEFAULT ((0)) FOR [caller_scream]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_ScreamInfo]  DEFAULT (N'无') FOR [caller_scream_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Call]  DEFAULT ((0)) FOR [caller_call]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_CallInfo]  DEFAULT (N'无') FOR [caller_call_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Cancel]  DEFAULT ((0)) FOR [caller_cancel]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_CancelInfo]  DEFAULT (N'无') FOR [caller_cancel_info]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_X]  DEFAULT ((0)) FOR [caller_x]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CALLER] ADD  CONSTRAINT [DF_AGVDB_INFO_CALLER_Y]  DEFAULT ((0)) FOR [caller_y]
GO
ALTER TABLE [dbo].[AGVDB_INFO_CHARGER] ADD  CONSTRAINT [DF_AGVDB_INFO_CHARGER_Location]  DEFAULT ((0)) FOR [charger_location]
GO
ALTER TABLE [dbo].[AGVDB_INFO_REST] ADD  CONSTRAINT [DF_AGVDB_INFO_RESET_Location]  DEFAULT ((0)) FOR [rester_location]
GO
ALTER TABLE [dbo].[AGVDB_TASK_CURRENT] ADD  CONSTRAINT [DF_AGVDB_TASK_CURRENT_task_executer]  DEFAULT ((0)) FOR [task_executer]
GO
ALTER TABLE [dbo].[AGVDB_TASK_CURRENT] ADD  CONSTRAINT [DF_AGVDB_TASK_CURRENT_task_status]  DEFAULT (N'未执行') FOR [task_status]
GO
ALTER TABLE [dbo].[AGVDB_TASK_CURRENT] ADD  CONSTRAINT [DF_AGVDB_TASK_CURRENT_task_publish]  DEFAULT (getdate()) FOR [task_publish]
GO
ALTER TABLE [dbo].[AGVDB_TASK_CURRENT] ADD  CONSTRAINT [DF_AGVDB_TASK_CURRENT_task_error]  DEFAULT (N'正常') FOR [task_error]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的类型' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_type'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的网络模式(bool).
true为客户端模式.
false为服务端模式.' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_client'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV网络模块的IP地址' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_ip'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV网络模块的端口' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_port'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'连接AGV时使用的本地IP地址' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_locol_ip'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'连接AGV时使用的本地端口' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_locol_port'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的连接状态' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_connection'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的当前坐标。即当前所在RFID地标卡编号。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_cur'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV目标坐标。即AGV移动终点RFID地标卡编号。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_target'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的运行状态' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_status'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV状态信息的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_status_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV剩余电量(%)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_battery'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV当前速度(%)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_speed'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV载货数量' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_cargo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV载货数量的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_cargo_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的当前动作' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_action'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的当前动作执行的状态' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_action_status'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV当前动作的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_action_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV的异常信息' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_error'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV异常信息的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV', @level2type=N'COLUMN',@level2name=N'agv_error_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'储存AGV参数配置以及实时运行状态的数据表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGV'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV类型名称' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_name'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV品牌' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_brand'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV型号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_version'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV最大速度' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_max_speed'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV最大载重量' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_max_weight'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV通信协议类型' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_protocol'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'AGV动作名称列表，JSON字符串' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE', @level2type=N'COLUMN',@level2name=N'type_action'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'储存AGV类型的数据表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_AGVTYPE'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器MAC地址' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_address'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器绑定的工作站编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_bind_station'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器的设备状态(bool)。
true为启用。
false为禁用。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_enable'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器急停信号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_scream'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器急停信号状态的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_scream_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器呼叫信号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_call'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器呼叫信号状态的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_call_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器取消信号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_cancel'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'呼叫器取消信号状态的文字说明' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER', @level2type=N'COLUMN',@level2name=N'caller_cancel_info'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'储存呼叫器配置信息以及呼叫器设备状态、实时信号状态的数据表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CALLER'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'充电站编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER', @level2type=N'COLUMN',@level2name=N'charger_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'充电站坐标。即充电站所在的RFID地标卡编号。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER', @level2type=N'COLUMN',@level2name=N'charger_location'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'充电站名称' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER', @level2type=N'COLUMN',@level2name=N'charger_name'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'充电站图标X坐标' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER', @level2type=N'COLUMN',@level2name=N'charger_x'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'充电站图标Y坐标' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER', @level2type=N'COLUMN',@level2name=N'charger_y'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'储存充电站配置的数据表' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_CHARGER'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'待机站编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_REST', @level2type=N'COLUMN',@level2name=N'rester_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'待机站坐标。即待机站所在RFID地标卡编号。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_REST', @level2type=N'COLUMN',@level2name=N'rester_location'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'待机站名称' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_REST', @level2type=N'COLUMN',@level2name=N'rester_name'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'JSON字符串。
储存锁定待机站的地标卡组。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_REST', @level2type=N'COLUMN',@level2name=N'rester_lock'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'待机队列编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_RESTQUEUE', @level2type=N'COLUMN',@level2name=N'queue_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'JSON字符串。
储存队列内待机站成员的以及成员的排列顺序。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_RESTQUEUE', @level2type=N'COLUMN',@level2name=N'queue_list'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'RFID地标卡编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_RFID', @level2type=N'COLUMN',@level2name=N'rfid_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'RFID图标X坐标' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_RFID', @level2type=N'COLUMN',@level2name=N'rfid_x'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'RFID图标Y坐标' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_RFID', @level2type=N'COLUMN',@level2name=N'rfid_y'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'交通管制点RFID地标卡编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_TRAFFIC', @level2type=N'COLUMN',@level2name=N'traffic_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'JSON字符串。
储存锁定交通管制点的RFID地标卡组。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_TRAFFIC', @level2type=N'COLUMN',@level2name=N'traffic_lock'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'JSON字符串。
储存与交通管制点交互对比的交通管制RFID地标卡组。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_TRAFFIC', @level2type=N'COLUMN',@level2name=N'traffic_compare'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工作站编号' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_WORK', @level2type=N'COLUMN',@level2name=N'worker_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工作站坐标。即工作站所在RFID地标卡编号。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_WORK', @level2type=N'COLUMN',@level2name=N'worker_location'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工作站名称' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_WORK', @level2type=N'COLUMN',@level2name=N'worker_name'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工作站图标X坐标。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_WORK', @level2type=N'COLUMN',@level2name=N'worker_x'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'工作站图标Y坐标。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_INFO_WORK', @level2type=N'COLUMN',@level2name=N'worker_y'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'订单号，由调度系统自动生成' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_order'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务编号，主键，自增' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_id'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'托盘码，由用户填写' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_tray'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'取货工位名称，由拣选系统填写' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_target'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'卸货工位名称，由拣选系统填写' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_mission'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'执行任务AGV编号，由调度系统填写' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_executer'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务执行状态,由调度系统更新。' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_status'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务发布时间，由拣选系统填写' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_publish'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务执行时间，由调度系统更新' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_execution'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务完成时间，由调度系统更新' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_finish'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'任务备注，若用户对任务进行了手动修改，则在此字段记录' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AGVDB_TASK_CURRENT', @level2type=N'COLUMN',@level2name=N'task_error'
GO
USE [master]
GO
ALTER DATABASE [AGVDB] SET  READ_WRITE 
GO
