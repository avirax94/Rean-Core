/*
SQLyog Ultimate v13.1.1 (64 bit)
MySQL - 5.7.32-log : Database - auth_rean
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`auth_rean` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `auth_rean`;

/*Table structure for table `promocion_inicial` */

DROP TABLE IF EXISTS `promocion_inicial`;

CREATE TABLE `promocion_inicial` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `idcuenta` int(11) DEFAULT NULL,
  `ip` varchar(15) DEFAULT NULL,
  `level80` int(11) DEFAULT NULL,
  `oro` int(11) DEFAULT NULL,
  `honor` int(11) DEFAULT NULL,
  `bolsas` int(11) DEFAULT NULL,
  `emblemas` int(11) DEFAULT NULL,
  `monturas` int(11) DEFAULT NULL,
  `profesiones` int(11) DEFAULT NULL,
  `pve` int(11) DEFAULT NULL,
  `pvp` int(11) DEFAULT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

/*Data for the table `promocion_inicial` */

insert  into `promocion_inicial`(`id`,`idcuenta`,`ip`,`level80`,`oro`,`honor`,`bolsas`,`emblemas`,`monturas`,`profesiones`,`pve`,`pvp`) values 
(1,1,'127.0.0.1',1,1,1,1,1,2,2,1,1);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
