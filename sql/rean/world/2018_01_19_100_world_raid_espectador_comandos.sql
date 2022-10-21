-- Eilo (https://github.com/eilo)
-- Raid Espectador WowRean
-- Definición de los comandos

DELETE FROM `command` WHERE `name`='raidespectador';
INSERT INTO `command` (`name`, `permission`, `help`) VALUES
('raidespectador', 1001, 'Sintaxis: .raidespectador\nDesplega las opciones del comando.');

DELETE FROM `command` WHERE `name`='raidespectador entrar';
INSERT INTO `command` (`name`, `permission`, `help`) VALUES
('raidespectador entrar', 1002, 'Sintaxis: .raidespectador entrar idraid\nTe teletransporta en modo espectador al id de raid seleccionado.');

DELETE FROM `command` WHERE `name`='raidespectador salir';
INSERT INTO `command` (`name`, `permission`, `help`) VALUES
('raidespectador salir', 1003, 'Sintaxis: .raidespectador salir\nTe regresa al lugar antes de teletransportarte, dejando dejando de espectar el raid.');
