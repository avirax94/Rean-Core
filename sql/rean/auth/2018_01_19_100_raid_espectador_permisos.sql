-- Eilo (https://github.com/eilo)
-- Raid Espectador WowRean
-- Permisos y Roles para los comandos de Raid Espectador

-- Añadiendo el comando 1001 (.raidespectador) a la lista de permisos
DELETE FROM `rbac_permissions` WHERE `id` = 1001;
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES (1001, "Comando: raidespectador");

-- Asociando el comando 1001 (.raidespectador) con el rol 199 (player comun y silvestre)
DELETE FROM `rbac_linked_permissions` WHERE `id` = 199 and `linkedId` = 1001;
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES (199, 1001);

-- Añadiendo el comando 1003 (.raidespectador entrar) a la lista de permisos
DELETE FROM `rbac_permissions` WHERE `id` = 1002;
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES (1002, "Comando: raidespectador entrar");

-- Asociando el comando 1003 (.raidespectador entrar) con el rol 199 (player comun y silvestre)
DELETE FROM `rbac_linked_permissions` WHERE `id` = 199 and `linkedId` = 1002;
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES (199, 1002);

-- Añadiendo el comando 1004 (.raidespectador salir) a la lista de permisos
DELETE FROM `rbac_permissions` WHERE `id` = 1003;
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES (1003, "Comando: raidespectador salir");

-- Asociando el comando 1004 (.raidespectador salir) con el rol 199 (player comun y silvestre)
DELETE FROM `rbac_linked_permissions` WHERE `id` = 199 and `linkedId` = 1003;
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES (199, 1003);
