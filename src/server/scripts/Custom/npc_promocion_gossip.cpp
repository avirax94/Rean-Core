#include "ScriptMgr.h"
#include "AchievementMgr.h"
#include "Guild.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "DatabaseEnv.h"
#include "WorldSession.h"
#include "SpellMgr.h"
#include <sstream>

class npc_promocion_gossip : public CreatureScript
{
public:
	npc_promocion_gossip() : CreatureScript("npc_promocion") {}
	enum ClassMask
	{
		WARRIOR = 1,
		PALADIN = 2,
		HUNTER = 4,
		ROGUE = 8,
		PRIEST = 16,
		DK = 32,
		CHAMAN = 64,
		MAGO = 128,
		BRUJO = 256,
		DRUIDA = 1024
	};
	enum MenusPrincipales
	{
		LEVEL80 = 1,
		ORO = 2,
		MONTURA = 3,
		HONOR = 4,
		BOLSAS = 5,
		PVE = 7,
		PVP = 8,
		PROFESIONES = 9,
		SALIR = 10,
		GUILD = 11,
		ACEPTAR_TRIUNFO = 12,
	};
	enum MenuMonturas
	{
		MECAJARLY = 41508,
		CHOPPER = 44413,
		DRACOABISAL = 30609,
		PROTODRACOAPESTADO = 44175,
		CENIZAS = 32458,
		PROTODRACOAZUL = 44151,
		HIPOCENARION = 33999,
		MIMIRON = 45693,
		GLADIADORMORATAL = 46708,
		X51 = 49286,
		PROTODRACOTIEMPO = 44168,
		CRISTALRESONADOR = 21176,
		LORDCUERVO = 32768,
		TIGREESPECTRAL = 49284,
		GALLOMAGICO = 49290,
		INVENCIBLE = 50818,
		COHETEAMOR = 50250,
		CORCELCELESTIAL = 54811,
		GRANOSO = 43599,
		DRACOALBINO = 44178,
		DRACOVERIDIANA = 32861,
		DRACOAZUL = 43953,
	};
	enum MenuProfesiones
	{
		ENCANTAMIENTO = 333,
		INGENIERIA = 202,
		INSCRIPCION = 773,
		HERRERIA = 164,
		JOYERIA = 755,
		PELETERIA = 165,
		SASTRERIA = 197,
		ALQUIMIA = 171,
		DESUELLO = 393,
		HERBORISTERIA = 182,
		MINERIA = 186,
		COCINA = 185,
		PESCA = 356,
		PAUXILIOS = 129
	};
	enum MenuSets
	{
		PRIEST_HEALER = 1,
		PRIEST_DPS = 2,
		ROGUE_DPS = 3,
		MAGE_DPS = 4,
		WARLOCK_DPS = 5,
		PALA_DPS = 6,
		PALA_TANK = 7,
		PALA_HEALER = 8,
		PALA_DPS_TANK = 9,
		HUNTER_DPS = 11,
		WAR_DPS = 12,
		WAR_TANK = 13,
		DUDU_DPS = 14,
		DUDU_DPS_TANK = 15,
		DUDU_HEAL = 16,
		DK_TANK = 17,
		DK_DPS = 18,
		CHAMAN_HEAL = 19,
		CHAMAN_DPS = 20,
		WAR_DPS_TANK = 21,
		CHAMAN_ENCHANTED = 22,
	};
	enum WeaponSkillSpells
	{
		SPELL_BLOCK = 107,
		SPELL_BOWS = 264,
		SPELL_CROSSBOWS = 5011,
		SPELL_DAGGERS = 1180,
		SPELL_DUAL_WIELD = 674,
		SPELL_FIST_WEAPONS = 15590,
		SPELL_GUNS = 266,
		SPELL_MAIL = 8737,
		SPELL_PLATE = 750,
		SPELL_ONE_HANDED_AXES = 196,
		SPELL_ONE_HANDED_MACES = 198,
		SPELL_ONE_HANDED_SWORDS = 201,
		SPELL_TWO_HANDED_AXES = 197,
		SPELL_TWO_HANDED_MACES = 199,
		SPELL_TWO_HANDED_SWORDS = 202,
		SPELL_STAVES = 227,
		SPELL_THROW = 2764,
		SPELL_THROWN = 2567,
		SPELL_POLEARMS = 200,
		SPELL_RELIC = 52665,
		SPELL_RELIC_2 = 27764,
		SPELL_RELIC_3 = 27762,
		SPELL_RELIC_4 = 27763,
		SPELL_SHIELD = 9116,
		SPELL_SHOOT = 3018,
		SPELL_SHOOT_WANDS = 5019,
		SPELL_WANDS = 5009
	};
	enum Emblemas
	{
		ESCARCHA = 49426,
		TRIUNFO = 47241,
	};
	struct npc_PromocionAI : public ScriptedAI
	{
		npc_PromocionAI(Creature* creature) : ScriptedAI(creature) { }
		bool GossipHello(Player *player) override
		{
			player->PlayerTalkClass->ClearMenus();
			AddGossipItemFor(player, 0, "Subeme a nivel 80", GOSSIP_SENDER_MAIN, LEVEL80);
			AddGossipItemFor(player, 0, "Dame el oro", GOSSIP_SENDER_MAIN, ORO);
			AddGossipItemFor(player, 0, "Quiero elegir montura", GOSSIP_SENDER_MAIN, MONTURA);
			AddGossipItemFor(player, 0, "Dame el Honor", GOSSIP_SENDER_MAIN, HONOR);
			AddGossipItemFor(player, 0, "Y mis bolsas?", GOSSIP_SENDER_MAIN, BOLSAS);
			AddGossipItemFor(player, 0, "Equipo PvE", GOSSIP_SENDER_MAIN, PVE);
			AddGossipItemFor(player, 0, "Equipo PvP", GOSSIP_SENDER_MAIN, PVP);
			AddGossipItemFor(player, 0, "Veamos las profesiones", GOSSIP_SENDER_MAIN, PROFESIONES);
            //if (player->GetGuildId() != 0)AddGossipItemFor(player, 0, "Emblemas de escarcha", GOSSIP_SENDER_MAIN, ESCARCHA);
            //else AddGossipItemFor(player, 0, "Emblemas de triunfo", GOSSIP_SENDER_MAIN, TRIUNFO);
			AddGossipItemFor(player, 0, "Emblemas de triunfo", GOSSIP_SENDER_MAIN, TRIUNFO);
			//AddGossipItemFor(player, 0, "Recompensas de Hermandad (+15)", GOSSIP_SENDER_MAIN, GUILD);
			AddGossipItemFor(player, 3, "Salir", GOSSIP_SENDER_MAIN, SALIR);
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
			return true;
		}
bool GossipSelect(Player *player, uint32 /*menuId*/, uint32 gossipListId) override
		{
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			if (!player) return false;
			//Guild *hermandad;
			QueryResult resultado = CharacterDatabase.PQuery("SELECT characters.account FROM characters WHERE characters.guid = %d", player->GetGUID());
			int cuenta = resultado->Fetch()[0].GetUInt32();
			resultado = LoginDatabase.PQuery("SELECT last_ip FROM account WHERE id = %d", cuenta);
			std::string ip = resultado->Fetch()[0].GetString();
			player->PlayerTalkClass->ClearMenus();
			switch (sender)
			{
			case GOSSIP_SENDER_MAIN:
				switch (action)
				{
#pragma region Level80
				case LEVEL80:
					resultado = LoginDatabase.PQuery("SELECT level80 FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						player->GiveLevel(80);
						LearnSpells(player);
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip, level80) value (%d,'%s',1)", cuenta, ip);
						player->GetSession()->SendAreaTriggerMessage("Personaje a nivel 80");
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->GiveLevel(80);
							LearnSpells(player);
							LoginDatabase.PExecute("update promocion_inicial set level80 = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
							player->GetSession()->SendAreaTriggerMessage("Personaje a nivel 80");
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
						}
					}
					GossipHello(player);
					break;
#pragma endregion
#pragma region Oro
				case ORO:
					resultado = LoginDatabase.PQuery("SELECT oro FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						player->SetMoney(player->GetMoney() +10000000);
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip, oro) value (%d,'%s',1)", cuenta, ip);
						player->GetSession()->SendAreaTriggerMessage("Oro agregado");
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->SetMoney(player->GetMoney() +10000000);
							LoginDatabase.PExecute("update promocion_inicial set oro = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
							player->GetSession()->SendAreaTriggerMessage("Oro agregado");
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
						}
					}
					GossipHello(player);
					break;
#pragma endregion
#pragma region Montura
				case MONTURA:
					resultado = LoginDatabase.PQuery("SELECT monturas FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip) value (%d,'%s')", cuenta, ip);
						player->PlayerTalkClass->ClearMenus();
						AddGossipItemFor(player, 0, "Draco abisal veridiana", MONTURA, DRACOVERIDIANA);
						AddGossipItemFor(player, 0, "Protodraco apestado", MONTURA, PROTODRACOAPESTADO);
						AddGossipItemFor(player, 0, "Draco Azul", MONTURA, DRACOAZUL);
						AddGossipItemFor(player, 0, "Gallo magico", MONTURA, GALLOMAGICO);
						AddGossipItemFor(player, 0, "Draco Albino", MONTURA, DRACOALBINO);
						AddGossipItemFor(player, 3, "Atras", MONTURA, SALIR);
						SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
					}
					else
					{
						if (resultado->Fetch()[0].GetInt32() < 2)
						{
							player->PlayerTalkClass->ClearMenus();
							AddGossipItemFor(player, 0, "Draco abisal veridiana", MONTURA, DRACOVERIDIANA);
							AddGossipItemFor(player, 0, "Protodraco apestado", MONTURA, PROTODRACOAPESTADO);
							AddGossipItemFor(player, 0, "Draco Azul", MONTURA, DRACOAZUL);
							AddGossipItemFor(player, 0, "Gallo magico", MONTURA, GALLOMAGICO);
							AddGossipItemFor(player, 0, "Draco Albino", MONTURA, DRACOALBINO);
							AddGossipItemFor(player, 3, "Atras", MONTURA, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
							GossipHello(player);
						}
					}
					break;
#pragma endregion
#pragma region Honor
				case HONOR:
					resultado = LoginDatabase.PQuery("SELECT honor FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						player->SetHonorPoints(75000);
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip, honor) value (%d,'%s',1)", cuenta, ip);
						player->GetSession()->SendAreaTriggerMessage("Puntos de honor agregados");
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->SetHonorPoints(75000);
							LoginDatabase.PExecute("update promocion_inicial set honor = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
							player->GetSession()->SendAreaTriggerMessage("Puntos de honor agregados");
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
						}
					}
					GossipHello(player);
					break;
#pragma endregion
#pragma region Bolsas
				case BOLSAS:
					resultado = LoginDatabase.PQuery("SELECT bolsas FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						player->AddItem(41599, 4);
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip, bolsas) value (%d,'%s',1)", cuenta, ip);
						player->GetSession()->SendAreaTriggerMessage("Bolsas agregadas");
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->AddItem(41599, 4);
							LoginDatabase.PExecute("update promocion_inicial set bolsas = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
							player->GetSession()->SendAreaTriggerMessage("Bolsas agregadas");
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
						}
					}
					GossipHello(player);
					break;
#pragma endregion
#pragma region PvE
				case PVE:
					resultado = LoginDatabase.PQuery("SELECT pve FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip) value (%d,'%s')", cuenta, ip);
						player->PlayerTalkClass->ClearMenus();
						switch (player->getClassMask())
						{
						case PRIEST:
							AddGossipItemFor(player, 0, "DPS", PVE, PRIEST_DPS);
							AddGossipItemFor(player, 0, "SANADOR", PVE, PRIEST_HEALER);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case PALADIN:
							AddGossipItemFor(player, 0, "DPS", PVE, PALA_DPS);
							AddGossipItemFor(player, 0, "SANADOR", PVE, PALA_HEALER);
							AddGossipItemFor(player, 0, "TANQUE", PVE, PALA_TANK);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case ROGUE:
							AddGossipItemFor(player, 0, "DPS", PVE, ROGUE_DPS);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case MAGO:
							AddGossipItemFor(player, 0, "DPS", PVE, MAGE_DPS);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case BRUJO:
							AddGossipItemFor(player, 0, "DPS", PVE, WARLOCK_DPS);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case WARRIOR:
							AddGossipItemFor(player, 0, "DPS", PVE, WAR_DPS);
							AddGossipItemFor(player, 0, "TANQUE", PVE, WAR_TANK);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case DRUIDA:
							AddGossipItemFor(player, 0, "DPS", PVE, DUDU_DPS);
							AddGossipItemFor(player, 0, "FERAL", PVE, DUDU_DPS_TANK);
							AddGossipItemFor(player, 0, "SANADOR", PVE, DUDU_HEAL);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case DK:
							AddGossipItemFor(player, 0, "DPS", PVE, DK_DPS);
							AddGossipItemFor(player, 0, "TANQUE", PVE, DK_TANK);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case CHAMAN:
							AddGossipItemFor(player, 0, "DPS ELEMENTAL", PVE, CHAMAN_DPS);
							AddGossipItemFor(player, 0, "DPS MEJORA", PVE, CHAMAN_ENCHANTED);
							AddGossipItemFor(player, 0, "SANADOR", PVE, CHAMAN_HEAL);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case HUNTER:
							AddGossipItemFor(player, 0, "DPS", PVE, HUNTER_DPS);
							AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						default:
							player->GetSession()->SendNotification("Clase no reconocida");
							GossipHello(player);
							break;
						}
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->PlayerTalkClass->ClearMenus();
							switch (player->getClassMask())
							{
							case PRIEST:
								AddGossipItemFor(player, 0, "DPS", PVE, PRIEST_DPS);
								AddGossipItemFor(player, 0, "SANADOR", PVE, PRIEST_HEALER);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case PALADIN:
								AddGossipItemFor(player, 0, "DPS", PVE, PALA_DPS);
								AddGossipItemFor(player, 0, "SANADOR", PVE, PALA_HEALER);
								AddGossipItemFor(player, 0, "TANQUE", PVE, PALA_TANK);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case ROGUE:
								AddGossipItemFor(player, 0, "DPS", PVE, ROGUE_DPS);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case MAGO:
								AddGossipItemFor(player, 0, "DPS", PVE, MAGE_DPS);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case BRUJO:
								AddGossipItemFor(player, 0, "DPS", PVE, WARLOCK_DPS);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case WARRIOR:
								AddGossipItemFor(player, 0, "DPS", PVE, WAR_DPS);
								AddGossipItemFor(player, 0, "TANQUE", PVE, WAR_TANK);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case DRUIDA:
								AddGossipItemFor(player, 0, "DPS", PVE, DUDU_DPS);
								AddGossipItemFor(player, 0, "FERAL", PVE, DUDU_DPS_TANK);
								AddGossipItemFor(player, 0, "SANADOR", PVE, DUDU_HEAL);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case DK:
								AddGossipItemFor(player, 0, "DPS", PVE, DK_DPS);
								AddGossipItemFor(player, 0, "TANQUE", PVE, DK_TANK);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case CHAMAN:
								AddGossipItemFor(player, 0, "DPS ELEMENTAL", PVE, CHAMAN_DPS);
								AddGossipItemFor(player, 0, "DPS MEJORA", PVE, CHAMAN_ENCHANTED);
								AddGossipItemFor(player, 0, "SANADOR", PVE, CHAMAN_HEAL);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case HUNTER:
								AddGossipItemFor(player, 0, "DPS", PVE, HUNTER_DPS);
								AddGossipItemFor(player, 3, "Atras", PVE, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							default:
								player->GetSession()->SendNotification("Clase no reconocida");
								GossipHello(player);
								break;
							}
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
							GossipHello(player);
						}
					}
					break;
#pragma endregion
#pragma region PvP
				case PVP:
					resultado = LoginDatabase.PQuery("SELECT pvp FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);;
					if (!resultado)
					{
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip) value (%d,'%s')", cuenta, ip);
						player->PlayerTalkClass->ClearMenus();
						switch (player->getClassMask())
						{
						case PRIEST:
							AddGossipItemFor(player, 0, "DPS", PVP, PRIEST_DPS);
							AddGossipItemFor(player, 0, "SANADOR", PVP, PRIEST_HEALER);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player,
							DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case PALADIN:
							AddGossipItemFor(player, 0, "DPS/TANQUE", PVP, PALA_DPS_TANK);
							AddGossipItemFor(player, 0, "SANADOR", PVP, PALA_HEALER);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case ROGUE:
							AddGossipItemFor(player, 0, "DPS", PVP,
							ROGUE_DPS);
							AddGossipItemFor(player, 3, "Atras", PVP,
							SALIR);
							SendGossipMenuFor(player,
							DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case MAGO:
							AddGossipItemFor(player, 0, "DPS", PVP,
							MAGE_DPS);
							AddGossipItemFor(player, 3, "Atras", PVP,
							SALIR);
							SendGossipMenuFor(player,
							DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case BRUJO:
							AddGossipItemFor(player, 0, "DPS", PVP, WARLOCK_DPS);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case WARRIOR:
							AddGossipItemFor(player, 0, "DPS/TANQUE", PVP, WAR_DPS_TANK);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case DRUIDA:
							AddGossipItemFor(player, 0, "DPS", PVP, DUDU_DPS);
							AddGossipItemFor(player, 0, "FERAL", PVP, DUDU_DPS_TANK);
							AddGossipItemFor(player, 0, "SANADOR", PVP, DUDU_HEAL);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case DK:
							AddGossipItemFor(player, 0, "DPS", PVP, DK_DPS);
							AddGossipItemFor(player, 0, "TANQUE", PVP, DK_TANK);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case CHAMAN:
							AddGossipItemFor(player, 0, "DPS ELEMENTAL", PVP, CHAMAN_DPS);
							AddGossipItemFor(player, 0, "DPS MEJORA", PVP, CHAMAN_ENCHANTED);
							AddGossipItemFor(player, 0, "SANADOR", PVP, CHAMAN_HEAL);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						case HUNTER:
							AddGossipItemFor(player, 0, "DPS", PVP, HUNTER_DPS);
							AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
							break;
						default:
							player->GetSession()->SendNotification("Clase no reconocida");
							GossipHello(player);
							break;
						}
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->PlayerTalkClass->ClearMenus();
							switch (player->getClassMask())
							{
							case PRIEST:
								AddGossipItemFor(player, 0, "DPS", PVP, PRIEST_DPS);
								AddGossipItemFor(player, 0, "SANADOR", PVP, PRIEST_HEALER);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case PALADIN:
								AddGossipItemFor(player, 0, "DPS/TANQUE", PVP, PALA_DPS_TANK);
								AddGossipItemFor(player, 0, "SANADOR", PVP, PALA_HEALER);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case ROGUE:
								AddGossipItemFor(player, 0, "DPS", PVP, ROGUE_DPS);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case MAGO:
								AddGossipItemFor(player, 0, "DPS", PVP, MAGE_DPS);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case BRUJO:
								AddGossipItemFor(player, 0, "DPS", PVP, WARLOCK_DPS);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case WARRIOR:
								AddGossipItemFor(player, 0, "DPS/TANQUE", PVP, WAR_DPS_TANK);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case DRUIDA:
								AddGossipItemFor(player, 0, "DPS", PVP, DUDU_DPS);
								AddGossipItemFor(player, 0, "FERAL", PVP, DUDU_DPS_TANK);
								AddGossipItemFor(player, 0, "SANADOR", PVP, DUDU_HEAL);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case DK:
								AddGossipItemFor(player, 0, "DPS", PVP, DK_DPS);
								AddGossipItemFor(player, 0, "TANQUE", PVP, DK_TANK);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case CHAMAN:
								AddGossipItemFor(player, 0, "DPS ELEMENTAL", PVP, CHAMAN_DPS);
								AddGossipItemFor(player, 0, "DPS MEJORA", PVP, CHAMAN_ENCHANTED);
								AddGossipItemFor(player, 0, "SANADOR", PVP, CHAMAN_HEAL);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							case HUNTER:
								AddGossipItemFor(player, 0, "DPS", PVP, HUNTER_DPS);
								AddGossipItemFor(player, 3, "Atras", PVP, SALIR);
								SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
								break;
							default:
								player->GetSession()->SendNotification("Clase no reconocida");
								GossipHello(player);
								break;
							}
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
							GossipHello(player);
						}
					}
					break;
#pragma endregion
#pragma region Profesiones
				case PROFESIONES:
					resultado = LoginDatabase.PQuery("SELECT profesiones FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip) value (%d,'%s')", cuenta, ip);
						player->PlayerTalkClass->ClearMenus();
						AddGossipItemFor(player, 0, "Encantamiento", PROFESIONES, ENCANTAMIENTO);
						AddGossipItemFor(player, 0, "Ingenieria", PROFESIONES, INGENIERIA);
						AddGossipItemFor(player, 0, "Inscripcion", PROFESIONES, INSCRIPCION);
						AddGossipItemFor(player, 0, "Herreria", PROFESIONES, HERRERIA);
						AddGossipItemFor(player, 0, "Joyeria", PROFESIONES, JOYERIA);
						AddGossipItemFor(player, 0, "Peleteria", PROFESIONES, PELETERIA);
						AddGossipItemFor(player, 0, "Sastreria", PROFESIONES, SASTRERIA);
						AddGossipItemFor(player, 0, "Alquimia", PROFESIONES, ALQUIMIA);
						AddGossipItemFor(player, 0, "Desuello", PROFESIONES, DESUELLO);
						AddGossipItemFor(player, 0, "Herboristeria", PROFESIONES, HERBORISTERIA);
						AddGossipItemFor(player, 0, "Mineria", PROFESIONES, MINERIA);
						AddGossipItemFor(player, 0, "Primeros Auxilios", PROFESIONES, PAUXILIOS);
						AddGossipItemFor(player, 0, "Cocina", PROFESIONES, COCINA);
						AddGossipItemFor(player, 0, "Pesca", PROFESIONES, PESCA);
						AddGossipItemFor(player, 3, "Atras", PROFESIONES, SALIR);
						SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
					}
					else
					{
						if (resultado->Fetch()[0].GetInt32() < 2)
						{
							AddGossipItemFor(player, 0, "Encantamiento", PROFESIONES, ENCANTAMIENTO);
							AddGossipItemFor(player, 0, "Ingenieria", PROFESIONES, INGENIERIA);
							AddGossipItemFor(player, 0, "Inscripcion", PROFESIONES, INSCRIPCION);
							AddGossipItemFor(player, 0, "Herreria", PROFESIONES, HERRERIA);
							AddGossipItemFor(player, 0, "Joyeria", PROFESIONES, JOYERIA);
							AddGossipItemFor(player, 0, "Peleteria", PROFESIONES, PELETERIA);
							AddGossipItemFor(player, 0, "Sastreria", PROFESIONES, SASTRERIA);
							AddGossipItemFor(player, 0, "Alquimia", PROFESIONES, ALQUIMIA);
							AddGossipItemFor(player, 0, "Desuello", PROFESIONES, DESUELLO);
							AddGossipItemFor(player, 0, "Herboristeria", PROFESIONES, HERBORISTERIA);
							AddGossipItemFor(player, 0, "Mineria", PROFESIONES, MINERIA);
							AddGossipItemFor(player, 0, "Primeros Auxilios", PROFESIONES, PAUXILIOS);
							AddGossipItemFor(player, 0, "Cocina", PROFESIONES, COCINA);
							AddGossipItemFor(player, 0, "Pesca", PROFESIONES, PESCA);
							AddGossipItemFor(player, 3, "Atras", PROFESIONES, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
							GossipHello(player);
						}
					}
					break;
#pragma endregion
/*#pragma region Hermandad
				case GUILD:
					hermandad = player->GetGuild();
					if (hermandad)
					{
						if (hermandad->GetLeaderGUID() == player->GetGUID())
						{
							if (hermandad->GetMemberCount() >= 15)
							{
								uint32 BankTabCount = hermandad->GetBankTabCount();
								if (BankTabCount < 6)
								{
									uint32 MoneyForPeople = 5000000 * hermandad->GetMemberCount();
									uint32 MoneyForBankTab = 0;
									for (int i = BankTabCount; i < 6; i++) MoneyForBankTab = MoneyForBankTab + hermandad->GetGuildBankTabPrice(i);
									player->ModifyMoney(MoneyForBankTab + MoneyForPeople);
									hermandad->HandleMemberDepositMoney(player->GetSession(), MoneyForPeople);
									for (int i = 0; i < 6; i++)
										hermandad->HandleBuyBankTab(player->GetSession(), i);
									player->GetSession()->SendAreaTriggerMessage("Promocion aplicada");
								}
								else
									player->GetSession()->SendNotification("La promocion ya estaba aplicada");
							}
							else
								player->GetSession()->SendNotification("La hermandad no tiene suficiente gente");
						}
						else player->GetSession()->SendNotification("Solo puede solicitar la poromocion el Lider");
					}
					else player->GetSession()->SendNotification("No tienes Hermandad");
					GossipHello(player);
					break;
#pragma endregion*/
#pragma region ESCARCHA
				case ESCARCHA:
					resultado = LoginDatabase.PQuery("SELECT emblemas FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						player->AddItem(ESCARCHA, 500);
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip, emblemas) value (%d,'%s',1)", cuenta, ip);
						player->GetSession()->SendAreaTriggerMessage("Has recibido 500 emblemas de escharcha");
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							player->AddItem(ESCARCHA, 500);
							LoginDatabase.PExecute("update promocion_inicial set emblemas = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
							player->GetSession()->SendAreaTriggerMessage("Has recibido 500 emblemas de escharcha");
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
						}
					}
					GossipHello(player);
					break;
#pragma endregion
#pragma region TRIUNFO
				case TRIUNFO:
					resultado = LoginDatabase.PQuery("SELECT emblemas FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					if (!resultado)
					{
						LoginDatabase.PExecute("insert into promocion_inicial (idcuenta,ip) value (%d,'%s')", cuenta, ip);
						AddGossipItemFor(player, 0, "SI, quiero los emblemas de triunfo aunque despues no pueda obtener los de escarcha si tengo guild", TRIUNFO, ACEPTAR_TRIUNFO);
						AddGossipItemFor(player, 3, "NO, voy a esperar a tener guild para conseguir emblemas de escarcha", TRIUNFO, SALIR);
						SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
					}
					else
					{
						if (!resultado->Fetch()[0].GetBool())
						{
							AddGossipItemFor(player, 0, "SI, quiero los emblemas de triunfo aunque despues no pueda obtener los de escarcha si tengo guild", TRIUNFO, ACEPTAR_TRIUNFO);
							AddGossipItemFor(player, 3, "NO, voy a esperar a tener guild para conseguir emblemas de escarcha", TRIUNFO, SALIR);
							SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
						}
						else
						{
							player->GetSession()->SendNotification("Ya has aplicado la promocion en esta cuenta y/o IP");
							GossipHello(player);
						}
					}
					break;
#pragma endregion
#pragma region Salir
				case SALIR:
					CloseGossipMenuFor(player);
					break;
#pragma endregion
				}
				break;
			case MONTURA:
				switch (action)
				{
				case SALIR:
					GossipHello(player);
					break;
				default:
					player->AddItem(action, 1);
					resultado = LoginDatabase.PQuery("SELECT monturas FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					LoginDatabase.PExecute("update promocion_inicial set monturas = '%d' where idcuenta = %d or ip = '%s'", resultado->Fetch()[0].GetInt32() + 1, cuenta, ip);
					GossipHello(player);
					break;
				}
				break;
			case PROFESIONES:
				switch (action)
				{
				case SALIR:
					GossipHello(player);
					break;
				default:
					HandleLearnSkillRecipesHelper(player, action);
					uint16 maxLevel = player->GetPureMaxSkillValue(action);
					player->SetSkill(action, player->GetSkillStep(action),
					maxLevel, maxLevel);
					resultado = LoginDatabase.PQuery("SELECT profesiones FROM promocion_inicial WHERE idcuenta = %d or ip = '%s'", cuenta, ip);
					LoginDatabase.PExecute("update promocion_inicial set profesiones = '%d' where idcuenta = %d or ip = '%s'", resultado->Fetch()[0].GetInt32() + 1, cuenta, ip);
					GossipHello(player);
					break;
				}
				break;
			case PVE:
				switch (action)
				{
				case SALIR:
					GossipHello(player);
					break;
				case PRIEST_DPS:
//Set
					player->AddItem(39521, 1);
					player->AddItem(39529, 1);
					player->AddItem(39523, 1);
					player->AddItem(39530, 1);
					player->AddItem(39528, 1);
//Offset
					player->AddItem(47173, 1);
					player->AddItem(40696, 1);
					player->AddItem(39254, 1);
					player->AddItem(41610, 1);
					player->AddItem(39472, 1);
//Abalorios-anillos-arma
					player->AddItem(40682, 1);
					player->AddItem(39229, 1);
					player->AddItem(39389, 1);
					player->AddItem(39244, 1);
					player->AddItem(39473, 1);
//Arma
					player->AddItem(39256, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PRIEST_HEALER:
//Set
					player->AddItem(39514, 1);
					player->AddItem(39518, 1);
					player->AddItem(39515, 1);
					player->AddItem(39519, 1);
					player->AddItem(39517, 1);
//Offset
					player->AddItem(39252, 1);
					player->AddItem(40697, 1);
					player->AddItem(39254, 1);
					player->AddItem(41610, 1);
					player->AddItem(40681, 1);
//Abalorios-anillos-distancia
					player->AddItem(49078, 1);
					player->AddItem(39229, 1);
					player->AddItem(44934, 1);
					player->AddItem(39407, 1);
					player->AddItem(39473, 1);
//Arma
					player->AddItem(39394, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case ROGUE_DPS:
//Set
					player->AddItem(39561, 1);
					player->AddItem(39565, 1);
					player->AddItem(39558, 1);
					player->AddItem(39560, 1);
					player->AddItem(39564, 1);
//Offset
					player->AddItem(37853, 1);
					player->AddItem(40694, 1);
					player->AddItem(39196, 1);
					player->AddItem(39297, 1);
					player->AddItem(40678, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(47214, 1);
					player->AddItem(37642, 1);
					player->AddItem(44308, 1);
					player->AddItem(40716, 1);
//Arma
					player->AddItem(37667, 1);
					player->AddItem(44310, 1);
					player->AddItem(39226, 1);
					player->AddItem(45075, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case MAGE_DPS:
//Set
					player->AddItem(39491, 1);
					player->AddItem(39494, 1);
					player->AddItem(39492, 1);
					player->AddItem(39495, 1);
					player->AddItem(39493, 1);
//Offset
					player->AddItem(47173, 1);
					player->AddItem(40696, 1);
					player->AddItem(39254, 1);
					player->AddItem(41610, 1);
					player->AddItem(39472, 1);
//Abalorios-anillos-distancia
					player->AddItem(40682, 1);
					player->AddItem(39229, 1);
					player->AddItem(39389, 1);
					player->AddItem(39244, 1);
					player->AddItem(39473, 1);
//Arma
					player->AddItem(39256, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case WARLOCK_DPS:
//Set
					player->AddItem(39496, 1);
					player->AddItem(39499, 1);
					player->AddItem(39497, 1);
					player->AddItem(39500, 1);
					player->AddItem(39498, 1);
//Offset
					player->AddItem(47173, 1);
					player->AddItem(40696, 1);
					player->AddItem(39254, 1);
					player->AddItem(41610, 1);
					player->AddItem(39472, 1);
//Abalorios-anillos-distancia
					player->AddItem(40682, 1);
					player->AddItem(39229, 1);
					player->AddItem(39389, 1);
					player->AddItem(39244, 1);
					player->AddItem(39473, 1);
//Arma
					player->AddItem(39256, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PALA_DPS:
//Set
					player->AddItem(39635, 1);
					player->AddItem(39637, 1);
					player->AddItem(39633, 1);
					player->AddItem(39634, 1);
					player->AddItem(39636, 1);
//Offset
					player->AddItem(39195, 1);
					player->AddItem(39345, 1);
					player->AddItem(39139, 1);
					player->AddItem(47232, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(42987, 1);
					player->AddItem(39401, 1);
					player->AddItem(40426, 1);
					player->AddItem(40706, 1);
//Arma
					if (player->GetTeamId() == 1) player->AddItem(45205, 1);
					else if (player->GetTeamId() == 7)player->AddItem(45074,
						1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PALA_TANK:
//Set
					player->AddItem(39640, 1);
					player->AddItem(39642, 1);
					player->AddItem(39638, 1);
					player->AddItem(39639, 1);
					player->AddItem(39641, 1);
//Offset
					player->AddItem(39467, 1);
					player->AddItem(39298, 1);
					player->AddItem(39234, 1);
					player->AddItem(39225, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(40683, 1);
					player->AddItem(39141, 1);
					player->AddItem(40426, 1);
					player->AddItem(40426, 1);
//Arma
					player->AddItem(39344, 1);
//Escudo
					player->AddItem(39276, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PALA_HEALER:
//Set
					player->AddItem(39628, 1);
					player->AddItem(39631, 1);
					player->AddItem(39629, 1);
					player->AddItem(39632, 1);
					player->AddItem(39630, 1);
//Offset
					player->AddItem(39235, 1);
					player->AddItem(39261, 1);
					player->AddItem(41394, 1);
					player->AddItem(41610, 1);
					player->AddItem(40681, 1);
//Abalorios-anillos-distancia
					player->AddItem(49078, 1);
					player->AddItem(39229, 1);
					player->AddItem(44934, 1);
					player->AddItem(39407, 1);
					player->AddItem(40705, 1);
//Arma
					player->AddItem(39281, 1);
//Escudo
					player->AddItem(40700, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case WAR_DPS:
//Set
					player->AddItem(39605, 1);
					player->AddItem(39608, 1);
					player->AddItem(39606, 1);
					player->AddItem(39609, 1);
					player->AddItem(39607, 1);
//Offset
					player->AddItem(39195, 1);
					player->AddItem(39345, 1);
					player->AddItem(39139, 1);
					player->AddItem(47232, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(42987, 1);
					player->AddItem(39401, 1);
					player->AddItem(40426, 1);
					player->AddItem(44504, 1);
//Arma
					if (player->GetTeamId() == 1)
					{
						player->AddItem(45205, 2);
					}
					else if (player->GetTeamId() == 7)
					{
						player->AddItem(45074, 2);
					}
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case WAR_TANK:
//Set
					player->AddItem(39610, 1);
					player->AddItem(39613, 1);
					player->AddItem(39611, 1);
					player->AddItem(39622, 1);
					player->AddItem(39612, 1);
//Offset
					player->AddItem(39467, 1);
					player->AddItem(39298, 1);
					player->AddItem(39234, 1);
					player->AddItem(39225, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(40683, 1);
					player->AddItem(39141, 1);
					player->AddItem(40426, 1);
					player->AddItem(41168, 1);
//Arma
					player->AddItem(39344, 1);
//Escudo
					player->AddItem(39276, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_DPS:
//Set
					player->AddItem(39545, 1);
					player->AddItem(39548, 1);
					player->AddItem(39547, 1);
					player->AddItem(39544, 1);
					player->AddItem(39546, 1);
//Offset
					player->AddItem(39283, 1);
					player->AddItem(37643, 1);
					player->AddItem(44930, 1);
					player->AddItem(41610, 1);
					player->AddItem(39472, 1);
//Abalorios-anillos-distancia
					player->AddItem(40682, 1);
					player->AddItem(39229, 1);
					player->AddItem(39389, 1);
					player->AddItem(39244, 1);
					player->AddItem(40712, 1);
//Arma
					player->AddItem(39256, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_DPS_TANK:
//Set
					player->AddItem(39553, 1);
					player->AddItem(39556, 1);
					player->AddItem(39554, 1);
					player->AddItem(39557, 1);
					player->AddItem(39555, 1);
//Offset
					player->AddItem(37853, 1);
					player->AddItem(40694, 1);
					player->AddItem(39196, 1);
					player->AddItem(39297, 1);
					player->AddItem(40678, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(47214, 1);
					player->AddItem(37642, 1);
					player->AddItem(44308, 1);
					player->AddItem(40713, 1);
//Arma
					player->AddItem(39255, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_HEAL:
//Set
					player->AddItem(39531, 1);
					player->AddItem(39542, 1);
					player->AddItem(39538, 1);
					player->AddItem(39543, 1);
					player->AddItem(39539, 1);
//Offset
					player->AddItem(39283, 1);
					player->AddItem(39308, 1);
					player->AddItem(43502, 1);
					player->AddItem(41610, 1);
					player->AddItem(40681, 1);
//Abalorios-anillos-distancia
					player->AddItem(49078, 1);
					player->AddItem(39229, 1);
					player->AddItem(44934, 1);
					player->AddItem(39407, 1);
					player->AddItem(40711, 1);
//Arma
					player->AddItem(39394, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DK_DPS:
//Set
					player->AddItem(39619, 1);
					player->AddItem(39621, 1);
					player->AddItem(39617, 1);
					player->AddItem(39618, 1);
					player->AddItem(39620, 1);
//Offset
					player->AddItem(39195, 1);
					player->AddItem(39345, 1);
					player->AddItem(39139, 1);
					player->AddItem(47232, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(42987, 1);
					player->AddItem(39401, 1);
					player->AddItem(40426, 1);
					player->AddItem(40715, 1);
//Arma
					if (player->GetTeamId() == 1) player->AddItem(45205, 1);
					else if (player->GetTeamId() == 7)player->AddItem(45074,
						1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DK_TANK:
//Set
					player->AddItem(39625, 1);
					player->AddItem(39627, 1);
					player->AddItem(39623, 1);
					player->AddItem(39624, 1);
					player->AddItem(39626, 1);
//Offset
					player->AddItem(39467, 1);
					player->AddItem(39298, 1);
					player->AddItem(39234, 1);
					player->AddItem(39225, 1);
					player->AddItem(39470, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(40683, 1);
					player->AddItem(39141, 1);
					player->AddItem(40426, 1);
					player->AddItem(40715, 1);
//Arma
					player->AddItem(39344, 1);
//Escudo
					player->AddItem(39276, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_DPS:
//Set
					player->AddItem(39594, 1);
					player->AddItem(39596, 1);
					player->AddItem(39592, 1);
					player->AddItem(39593, 1);
					player->AddItem(39595, 1);
//Offset
					player->AddItem(37788, 1);
					player->AddItem(37855, 1);
					player->AddItem(43469, 1);
					player->AddItem(41610, 1);
					player->AddItem(39472, 1);
//Abalorios-anillos-distancia
					player->AddItem(40682, 1);
					player->AddItem(39229, 1);
					player->AddItem(39389, 1);
					player->AddItem(39244, 1);
					player->AddItem(40708, 1);
//Arma
					player->AddItem(39256, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_ENCHANTED:
//Set
					player->AddItem(39602, 1);
					player->AddItem(39604, 1);
					player->AddItem(39597, 1);
					player->AddItem(39601, 1);
					player->AddItem(39603, 1);
//Offset
					player->AddItem(47211, 1);
					player->AddItem(37407, 1);
					player->AddItem(39236, 1);
					player->AddItem(39297, 1);
					player->AddItem(40678, 1);
//Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(47214, 1);
					player->AddItem(37642, 1);
					player->AddItem(44308, 1);
					player->AddItem(40710, 1);
//Arma
					player->AddItem(39226, 1);
					player->AddItem(45075, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_HEAL:
//Set
					player->AddItem(39583, 1);
					player->AddItem(39590, 1);
					player->AddItem(39588, 1);
					player->AddItem(39591, 1);
					player->AddItem(39589, 1);
//Offset
					player->AddItem(39307, 1);
					player->AddItem(37855, 1);
					player->AddItem(39189, 1);
					player->AddItem(41610, 1);
					player->AddItem(40681, 1);
//Abalorios-anillos-distancia
					player->AddItem(49078, 1);
					player->AddItem(39229, 1);
					player->AddItem(44934, 1);
					player->AddItem(39407, 1);
					player->AddItem(40709, 1);
                    //Arma
					player->AddItem(39281, 1);
                    //Escudo
					player->AddItem(40700, 1);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case HUNTER_DPS:
                    //Set
					player->AddItem(39578, 1);
					player->AddItem(39581, 1);
					player->AddItem(39579, 1);
					player->AddItem(39582, 1);
					player->AddItem(39580, 1);
                    //Offset
					player->AddItem(47211, 1);
					player->AddItem(37407, 1);
					player->AddItem(39236, 1);
					player->AddItem(39297, 1);
					player->AddItem(40678, 1);
                    //Abalorios-anillos-distancia
					player->AddItem(40684, 1);
					player->AddItem(47214, 1);
					player->AddItem(37642, 1);
					player->AddItem(44308, 1);
					player->AddItem(39296, 1);
                    //Arma
					player->AddItem(37667, 1);
					player->AddItem(44310, 1);
                    //Flechas
					player->AddItem(10579, 500);
					LoginDatabase.PExecute("update promocion_inicial set pve = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				}
				break;
			case PVP:
				switch (action)
				{
				case SALIR:
					GossipHello(player);
					break;
				case PRIEST_DPS:
                    //Set
					player->AddItem(41913, 1);
					player->AddItem(41931, 1);
					player->AddItem(41919, 1);
					player->AddItem(41938, 1);
					player->AddItem(41925, 1);
                    //Offset
					player->AddItem(41878, 1);
					player->AddItem(41877, 1);
					player->AddItem(41879, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(42501, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PRIEST_HEALER:
                    //Set
					player->AddItem(41852, 1);
					player->AddItem(41867, 1);
					player->AddItem(41857, 1);
					player->AddItem(41872, 1);
					player->AddItem(41862, 1);
                    //Offset
					player->AddItem(41878, 1);
					player->AddItem(41877, 1);
					player->AddItem(41879, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(42501, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case ROGUE_DPS:
                    //Set
					player->AddItem(41670, 1);
					player->AddItem(41681, 1);
					player->AddItem(41648, 1);
					player->AddItem(41765, 1);
					player->AddItem(41653, 1);
                    //Offset
					player->AddItem(41830, 1);
					player->AddItem(41827, 1);
					player->AddItem(41828, 1);
					player->AddItem(42060, 1);
					player->AddItem(42060, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
                    //Arma
					player->AddItem(42247, 1);
					player->AddItem(42241, 1);
					player->AddItem(42207, 1);
					player->AddItem(42274, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case MAGE_DPS:
                    //Set
					player->AddItem(41944, 1);
					player->AddItem(41963, 1);
					player->AddItem(41950, 1);
					player->AddItem(41969, 1);
					player->AddItem(41957, 1);
                    //Offset
					player->AddItem(41878, 1);
					player->AddItem(41877, 1);
					player->AddItem(41879, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(42501, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case WARLOCK_DPS:
                    //Set
					player->AddItem(41991, 1);
					player->AddItem(42009, 1);
					player->AddItem(42001, 1);
					player->AddItem(42015, 1);
					player->AddItem(42003, 1);
                    //Offset
					player->AddItem(41878, 1);
					player->AddItem(41877, 1);
					player->AddItem(41879, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(42501, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PALA_DPS_TANK:
                    //Set
					player->AddItem(40821, 1);
					player->AddItem(40861, 1);
					player->AddItem(40782, 1);
					player->AddItem(40802, 1);
					player->AddItem(40842, 1);
                    //Offset
					player->AddItem(40887, 1);
					player->AddItem(40877, 1);
					player->AddItem(40878, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
					player->AddItem(47664, 1);
                    //Arma
					player->AddItem(42316, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case PALA_HEALER:
                    //Set
					player->AddItem(40931, 1);
					player->AddItem(40961, 1);
					player->AddItem(40904, 1);
					player->AddItem(40925, 1);
					player->AddItem(40937, 1);
                    //Offset
					player->AddItem(40972, 1);
					player->AddItem(40966, 1);
					player->AddItem(40973, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(42613, 1);
                    //Arma
					player->AddItem(42351, 1);
                    //Escudo
					player->AddItem(42563, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case WAR_DPS_TANK:
                    //Set
					player->AddItem(40819, 1);
					player->AddItem(40859, 1);
					player->AddItem(40783, 1);
					player->AddItem(40801, 1);
					player->AddItem(40840, 1);
                    //Offset
					player->AddItem(40887, 1);
					player->AddItem(40877, 1);
					player->AddItem(40878, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
                    //Arma
					player->AddItem(42316, 2);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_DPS:
                    //Set
					player->AddItem(41325, 1);
					player->AddItem(41279, 1);
					player->AddItem(41314, 1);
					player->AddItem(41291, 1);
					player->AddItem(41302, 1);
                    //Offset
					player->AddItem(41332, 1);
					player->AddItem(41330, 1);
					player->AddItem(41331, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(40712, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_DPS_TANK:
                    //Set
					player->AddItem(41676, 1);
					player->AddItem(41713, 1);
					player->AddItem(41659, 1);
					player->AddItem(41771, 1);
					player->AddItem(41665, 1);
                    //Offset
					player->AddItem(41830, 1);
					player->AddItem(41827, 1);
					player->AddItem(41828, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
					player->AddItem(40713, 1);
                    //Arma
					player->AddItem(42389, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DUDU_HEAL:
                    //Set
					player->AddItem(41319, 1);
					player->AddItem(41273, 1);
					player->AddItem(41308, 1);
					player->AddItem(41284, 1);
					player->AddItem(41296, 1);
                    //Offset
					player->AddItem(41332, 1);
					player->AddItem(41330, 1);
					player->AddItem(41331, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(40711, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case DK_DPS:
                    //Set
					player->AddItem(40820, 1);
					player->AddItem(40860, 1);
					player->AddItem(40781, 1);
					player->AddItem(40803, 1);
					player->AddItem(40841, 1);
                    //Offset
					player->AddItem(40887, 1);
					player->AddItem(40877, 1);
					player->AddItem(40878, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
					player->AddItem(40715, 1);
                    //Arma
					player->AddItem(42316, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_DPS:
                    //Set
					player->AddItem(41017, 1);
					player->AddItem(41042, 1);
					player->AddItem(40989, 1);
					player->AddItem(41005, 1);
					player->AddItem(41031, 1);
                    //Offset
					player->AddItem(48980, 1);
					player->AddItem(41050, 1);
					player->AddItem(41049, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(40708, 1);
                    //Arma
					player->AddItem(42359, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_ENCHANTED:
                    //Set
					player->AddItem(41149, 1);
					player->AddItem(41209, 1);
					player->AddItem(41079, 1);
					player->AddItem(41135, 1);
					player->AddItem(41162, 1);
                    //Offset
					player->AddItem(41047, 1);
					player->AddItem(41233, 1);
					player->AddItem(41228, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
					player->AddItem(40710, 1);
                    //Arma
					player->AddItem(42207, 1);
					player->AddItem(42274, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case CHAMAN_HEAL:
                    //Set
					player->AddItem(41011, 1);
					player->AddItem(41036, 1);
					player->AddItem(40988, 1);
					player->AddItem(40999, 1);
					player->AddItem(41025, 1);
                    //Offset
					player->AddItem(41047, 1);
					player->AddItem(41050, 1);
					player->AddItem(41049, 1);
					player->AddItem(42055, 1);
					player->AddItem(42022, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44912, 1);
					player->AddItem(48999, 1);
					player->AddItem(42110, 1);
					player->AddItem(40709, 1);
                    //Arma
					player->AddItem(42351, 1);
                    //Escudo
					player->AddItem(42563, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				case HUNTER_DPS:
                    //Set
					player->AddItem(41155, 1);
					player->AddItem(41215, 1);
					player->AddItem(41085, 1);
					player->AddItem(41141, 1);
					player->AddItem(41203, 1);
                    //Offset
					player->AddItem(41223, 1);
					player->AddItem(41233, 1);
					player->AddItem(41228, 1);
					player->AddItem(42060, 1);
					player->AddItem(42020, 1);
                    //Abalorios-anillos-arma
					player->AddItem(46084, 1);
					player->AddItem(44914, 1);
					player->AddItem(49000, 1);
					player->AddItem(42112, 1);
					player->AddItem(10579, 500);
                    //Arma
					player->AddItem(42489, 1);
					player->AddItem(42207, 1);
					player->AddItem(42236, 1);
					LoginDatabase.PExecute("update promocion_inicial set pvp = '1' where idcuenta = %d or ip = '%s'", cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Equipo agregado");
					GossipHello(player);
					break;
				}
				break;
			case TRIUNFO:
				switch (action)
				{
				case SALIR:
					GossipHello(player);
					break;
				default:
					player->AddItem(TRIUNFO, 500);
                    ////Damos tambien trofeos de la cruzada, para poder cojer el ser bueno
                    //player->AddItem(47242, 10);
					LoginDatabase.PExecute("update promocion_inicial set emblemas = '%d' where idcuenta = %d or ip = '%s'", 1, cuenta, ip);
					player->GetSession()->SendAreaTriggerMessage("Has recibido 500 emblemas de triunfo");
					GossipHello(player);
					break;
				}
				break;
			}
			return true;
		}
		static void HandleLearnSkillRecipesHelper(Player* player, uint32 skillId)
		{
			uint32 classmask = player->getClassMask();
			for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
			{
				SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
				if (!skillLine)
					continue;
// wrong skill
				if (skillLine->skillId != skillId)
					continue;
// not high rank
				if (skillLine->forward_spellid)
					continue;
// skip racial skills
				if (skillLine->racemask != 0)
					continue;
// skip wrong class skills
				if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;
				SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
				if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
					continue;
				player->LearnSpell(skillLine->spellId, false);
			}
		}
		void LearnSpells(Player* player)
		{
			switch (player->getClass())
			{
			case CLASS_DEATH_KNIGHT:
				DeathKnightSpells(player);
				break;
			case CLASS_DRUID:
				DruidSpells(player);
				break;
			case CLASS_HUNTER:
				HunterSpells(player);
				break;
			case CLASS_MAGE:
				MageSpells(player);
				break;
			case CLASS_PALADIN:
				PaladinSpells(player);
				break;
			case CLASS_PRIEST:
				PriestSpells(player);
				break;
			case CLASS_ROGUE:
				RogueSpells(player);
				break;
			case CLASS_SHAMAN:
				ShamanSpells(player);
				break;
			case CLASS_WARLOCK:
				WarlockSpells(player);
				break;
			case CLASS_WARRIOR:
				WarriorSpells(player);
				break;
			}
			RidingSpells(player);
			DualSpec(player);
			player->UpdateSkillsForLevel();
		}
		void DualSpec(Player* player)
		{
            player->CastSpell(player, 63680, true);
            player->CastSpell(player, 63624, true);
			//player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
			//player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
		}
		void RidingSpells(Player* player)
		{
			player->LearnSpell(33388, false);
			player->LearnSpell(33391, false);
			player->LearnSpell(34090, false);
			player->LearnSpell(34091, false);
			player->LearnSpell(54197, false);
		}
		void DeathKnightSpells(Player* player)
		{
			player->LearnSpell(SPELL_DUAL_WIELD, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_PLATE, true);
			player->LearnSpell(SPELL_POLEARMS, true);
			player->LearnSpell(SPELL_RELIC, true);
			player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
			player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
			player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
			player->LearnSpellHighestRank(48778);
			player->LearnSpellHighestRank(48266);
			player->LearnSpellHighestRank(50977);
			player->LearnSpellHighestRank(49576);
			player->LearnSpellHighestRank(49142);
			player->LearnSpellHighestRank(46584);
			player->LearnSpellHighestRank(48263);
			player->LearnSpellHighestRank(48528);
			player->LearnSpellHighestRank(45524);
			player->LearnSpellHighestRank(3714);
			player->LearnSpellHighestRank(48792);
			player->LearnSpellHighestRank(45529);
			player->LearnSpellHighestRank(56222);
			player->LearnSpellHighestRank(48743);
			player->LearnSpellHighestRank(56815);
			player->LearnSpellHighestRank(48707);
			player->LearnSpellHighestRank(48265);
			player->LearnSpellHighestRank(41999);
			player->LearnSpellHighestRank(47568);
			player->LearnSpellHighestRank(57623);
			player->LearnSpellHighestRank(49941);
			player->LearnSpellHighestRank(49909);
			player->LearnSpellHighestRank(51429);
			player->LearnSpellHighestRank(49916);
			player->LearnSpellHighestRank(42650);
			player->LearnSpellHighestRank(49930);
			player->LearnSpellHighestRank(49938);
			player->LearnSpellHighestRank(49895);
			player->LearnSpellHighestRank(49924);
			player->LearnSpellHighestRank(49921);
		}
		void DruidSpells(Player* player)
		{
			player->LearnSpell(SPELL_DAGGERS, true);
			player->LearnSpell(SPELL_FIST_WEAPONS, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_POLEARMS, true);
			player->LearnSpell(SPELL_RELIC_2, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
			player->LearnSpellHighestRank(5487);
			player->LearnSpellHighestRank(6795);
			player->LearnSpellHighestRank(18960);
			player->LearnSpellHighestRank(5229);
			player->LearnSpellHighestRank(8946);
			player->LearnSpellHighestRank(1066);
			player->LearnSpellHighestRank(768);
			player->LearnSpellHighestRank(2782);
			player->LearnSpellHighestRank(2893);
			player->LearnSpellHighestRank(5209);
			player->LearnSpellHighestRank(783);
			player->LearnSpellHighestRank(5225);
			player->LearnSpellHighestRank(22842);
			player->LearnSpellHighestRank(9634);
			player->LearnSpellHighestRank(20719);
			player->LearnSpellHighestRank(29166);
			player->LearnSpellHighestRank(22812);
			player->LearnSpellHighestRank(8983);
			player->LearnSpellHighestRank(18658);
			player->LearnSpellHighestRank(9913);
			player->LearnSpellHighestRank(33357);
			player->LearnSpellHighestRank(33786);
			player->LearnSpellHighestRank(26995);
			player->LearnSpellHighestRank(40120);
			player->LearnSpellHighestRank(62078);
			player->LearnSpellHighestRank(49802);
			player->LearnSpellHighestRank(53307);
			player->LearnSpellHighestRank(52610);
			player->LearnSpellHighestRank(48575);
			player->LearnSpellHighestRank(48476);
			player->LearnSpellHighestRank(48560);
			player->LearnSpellHighestRank(49803);
			player->LearnSpellHighestRank(48443);
			player->LearnSpellHighestRank(48562);
			player->LearnSpellHighestRank(53308);
			player->LearnSpellHighestRank(48577);
			player->LearnSpellHighestRank(53312);
			player->LearnSpellHighestRank(48574);
			player->LearnSpellHighestRank(48465);
			player->LearnSpellHighestRank(48570);
			player->LearnSpellHighestRank(48378);
			player->LearnSpellHighestRank(48480);
			player->LearnSpellHighestRank(48579);
			player->LearnSpellHighestRank(48477);
			player->LearnSpellHighestRank(50213);
			player->LearnSpellHighestRank(48461);
			player->LearnSpellHighestRank(48470);
			player->LearnSpellHighestRank(48467);
			player->LearnSpellHighestRank(48568);
			player->LearnSpellHighestRank(48451);
			player->LearnSpellHighestRank(48469);
			player->LearnSpellHighestRank(48463);
			player->LearnSpellHighestRank(48441);
			player->LearnSpellHighestRank(50763);
			player->LearnSpellHighestRank(49800);
			player->LearnSpellHighestRank(48572);
			player->LearnSpellHighestRank(48447);
		}
		void HunterSpells(Player* player)
		{
			player->LearnSpell(SPELL_BOWS, true);
			player->LearnSpell(SPELL_CROSSBOWS, true);
			player->LearnSpell(SPELL_DUAL_WIELD, true);
			player->LearnSpell(SPELL_FIST_WEAPONS, true);
			player->LearnSpell(SPELL_GUNS, true);
			player->LearnSpell(SPELL_MAIL, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_POLEARMS, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
			player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
			player->LearnSpellHighestRank(75);
			player->LearnSpellHighestRank(1494);
			player->LearnSpellHighestRank(13163);
			player->LearnSpellHighestRank(5116);
			player->LearnSpellHighestRank(883);
			player->LearnSpellHighestRank(2641);
			player->LearnSpellHighestRank(6991);
			player->LearnSpellHighestRank(982);
			player->LearnSpellHighestRank(1515);
			player->LearnSpellHighestRank(19883);
			player->LearnSpellHighestRank(20736);
			player->LearnSpellHighestRank(2974);
			player->LearnSpellHighestRank(6197);
			player->LearnSpellHighestRank(1002);
			player->LearnSpellHighestRank(19884);
			player->LearnSpellHighestRank(5118);
			player->LearnSpellHighestRank(34074);
			player->LearnSpellHighestRank(781);
			player->LearnSpellHighestRank(3043);
			player->LearnSpellHighestRank(1462);
			player->LearnSpellHighestRank(19885);
			player->LearnSpellHighestRank(3045);
			player->LearnSpellHighestRank(19880);
			player->LearnSpellHighestRank(13809);
			player->LearnSpellHighestRank(13161);
			player->LearnSpellHighestRank(5384);
			player->LearnSpellHighestRank(1543);
			player->LearnSpellHighestRank(19878);
			player->LearnSpellHighestRank(3034);
			player->LearnSpellHighestRank(13159);
			player->LearnSpellHighestRank(19882);
			player->LearnSpellHighestRank(14327);
			player->LearnSpellHighestRank(19879);
			player->LearnSpellHighestRank(19263);
			player->LearnSpellHighestRank(14311);
			player->LearnSpellHighestRank(19801);
			player->LearnSpellHighestRank(34026);
			player->LearnSpellHighestRank(27044);
			player->LearnSpellHighestRank(34600);
			player->LearnSpellHighestRank(34477);
			player->LearnSpellHighestRank(53271);
			player->LearnSpellHighestRank(49071);
			player->LearnSpellHighestRank(53338);
			player->LearnSpellHighestRank(49067);
			player->LearnSpellHighestRank(48996);
			player->LearnSpellHighestRank(49052);
			player->LearnSpellHighestRank(49056);
			player->LearnSpellHighestRank(49045);
			player->LearnSpellHighestRank(49001);
			player->LearnSpellHighestRank(61847);
			player->LearnSpellHighestRank(60192);
			player->LearnSpellHighestRank(61006);
			player->LearnSpellHighestRank(48990);
			player->LearnSpellHighestRank(53339);
			player->LearnSpellHighestRank(49048);
			player->LearnSpellHighestRank(58434);
		}
		void MageSpells(Player* player)
		{
			if (player->GetTeam() == ALLIANCE)
			{
// Portales Ali
				player->LearnSpellHighestRank(32266); // El Exodar
				player->LearnSpellHighestRank(11419); // Darnassus
				player->LearnSpellHighestRank(10059); // Ventormenta
				player->LearnSpellHighestRank(11416); // Forjaz
//Teleports Ali
				player->LearnSpellHighestRank(3565); // Darnassus
				player->LearnSpellHighestRank(32271); // El Exodar
				player->LearnSpellHighestRank(3562); // Forjaz
				player->LearnSpellHighestRank(3561); // Ventormenta
			}
			else
			{
//Portales Horda
				player->LearnSpellHighestRank(11420); // Cima trueno
				player->LearnSpellHighestRank(32267); // Lunargenta
				player->LearnSpellHighestRank(11418); // Entrañas
				player->LearnSpellHighestRank(11417); // Orgrimmar
//Teleports Horda
				player->LearnSpellHighestRank(3566); // Cima trueno
				player->LearnSpellHighestRank(3563); // Entrañas
				player->LearnSpellHighestRank(32272); // Lunargenta
				player->LearnSpellHighestRank(3567); // Orgrimmar
			}
			player->LearnSpellHighestRank(130);
			player->LearnSpellHighestRank(475);
			player->LearnSpellHighestRank(1953);
			player->LearnSpellHighestRank(12051);
			player->LearnSpellHighestRank(7301);
			player->LearnSpellHighestRank(2139);
			player->LearnSpellHighestRank(45438);
			player->LearnSpellHighestRank(12826);
			player->LearnSpellHighestRank(66);
			player->LearnSpellHighestRank(30449);
			player->LearnSpellHighestRank(53140);
			player->LearnSpellHighestRank(42917);
			player->LearnSpellHighestRank(43015);
			player->LearnSpellHighestRank(43017);
			player->LearnSpellHighestRank(42985);
			player->LearnSpellHighestRank(43010);
			player->LearnSpellHighestRank(42833);
			player->LearnSpellHighestRank(42914);
			player->LearnSpellHighestRank(42859);
			player->LearnSpellHighestRank(42846);
			player->LearnSpellHighestRank(43012);
			player->LearnSpellHighestRank(42842);
			player->LearnSpellHighestRank(43008);
			player->LearnSpellHighestRank(43024);
			player->LearnSpellHighestRank(43020);
			player->LearnSpellHighestRank(43046);
			player->LearnSpellHighestRank(42897);
			player->LearnSpellHighestRank(43002);
			player->LearnSpellHighestRank(42921);
			player->LearnSpellHighestRank(42940);
			player->LearnSpellHighestRank(42956);
			player->LearnSpellHighestRank(61316);
			player->LearnSpellHighestRank(61024);
			player->LearnSpellHighestRank(42973);
			player->LearnSpellHighestRank(47610);
			player->LearnSpellHighestRank(58659);
		}
		void PaladinSpells(Player* player)
		{
			if (player->GetTeam() == ALLIANCE)
			{
// Ally Charger
				player->LearnSpellHighestRank(23214);
			}
			else
			{
//Horde Charger
				player->LearnSpellHighestRank(34767);
			}
			player->LearnSpell(SPELL_BLOCK, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_PLATE, true);
			player->LearnSpell(SPELL_POLEARMS, true);
			player->LearnSpell(SPELL_RELIC_3, true);
			player->LearnSpell(SPELL_SHIELD, true);
			player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
			player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
			player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
			player->LearnSpellHighestRank(21084);
			player->LearnSpellHighestRank(20271);
			player->LearnSpellHighestRank(498);
			player->LearnSpellHighestRank(1152);
			player->LearnSpellHighestRank(53408);
			player->LearnSpellHighestRank(31789);
			player->LearnSpellHighestRank(62124);
			player->LearnSpellHighestRank(25780);
			player->LearnSpellHighestRank(1044);
			player->LearnSpellHighestRank(5502);
			player->LearnSpellHighestRank(19746);
			player->LearnSpellHighestRank(20164);
			player->LearnSpellHighestRank(10326);
			player->LearnSpellHighestRank(1038);
			player->LearnSpellHighestRank(53407);
			player->LearnSpellHighestRank(19752);
			player->LearnSpellHighestRank(20165);
			player->LearnSpellHighestRank(642);
			player->LearnSpellHighestRank(10278);
			player->LearnSpellHighestRank(20166);
			player->LearnSpellHighestRank(4987);
			player->LearnSpellHighestRank(6940);
			player->LearnSpellHighestRank(10308);
			player->LearnSpellHighestRank(25898);
			player->LearnSpellHighestRank(25899);
			player->LearnSpellHighestRank(32223);
			player->LearnSpellHighestRank(31801);
			player->LearnSpellHighestRank(33776);
			player->LearnSpellHighestRank(31884);
			player->LearnSpellHighestRank(54428);
			player->LearnSpellHighestRank(54043);
			player->LearnSpellHighestRank(48943);
			player->LearnSpellHighestRank(48936);
			player->LearnSpellHighestRank(48945);
			player->LearnSpellHighestRank(48938);
			player->LearnSpellHighestRank(48947);
			player->LearnSpellHighestRank(48817);
			player->LearnSpellHighestRank(48788);
			player->LearnSpellHighestRank(48932);
			player->LearnSpellHighestRank(48942);
			player->LearnSpellHighestRank(48801);
			player->LearnSpellHighestRank(48785);
			player->LearnSpellHighestRank(48934);
			player->LearnSpellHighestRank(48950);
			player->LearnSpellHighestRank(48819);
			player->LearnSpellHighestRank(48806);
			player->LearnSpellHighestRank(48782);
			player->LearnSpellHighestRank(53601);
			player->LearnSpellHighestRank(61411);
		}
		void PriestSpells(Player* player)
		{
			player->LearnSpell(SPELL_DAGGERS, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_SHOOT_WANDS, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_WANDS, true);
			player->LearnSpellHighestRank(586);
			player->LearnSpellHighestRank(2053);
			player->LearnSpellHighestRank(528);
			player->LearnSpellHighestRank(6346);
			player->LearnSpellHighestRank(453);
			player->LearnSpellHighestRank(8129);
			player->LearnSpellHighestRank(605);
			player->LearnSpellHighestRank(552);
			player->LearnSpellHighestRank(6064);
			player->LearnSpellHighestRank(1706);
			player->LearnSpellHighestRank(988);
			player->LearnSpellHighestRank(10909);
			player->LearnSpellHighestRank(10890);
			player->LearnSpellHighestRank(60931);
			player->LearnSpellHighestRank(10955);
			player->LearnSpellHighestRank(34433);
			player->LearnSpellHighestRank(32375);
			player->LearnSpellHighestRank(48072);
			player->LearnSpellHighestRank(48169);
			player->LearnSpellHighestRank(48168);
			player->LearnSpellHighestRank(48170);
			player->LearnSpellHighestRank(48120);
			player->LearnSpellHighestRank(48063);
			player->LearnSpellHighestRank(48135);
			player->LearnSpellHighestRank(48171);
			player->LearnSpellHighestRank(48300);
			player->LearnSpellHighestRank(48071);
			player->LearnSpellHighestRank(48127);
			player->LearnSpellHighestRank(48113);
			player->LearnSpellHighestRank(48123);
			player->LearnSpellHighestRank(48173);
			player->LearnSpellHighestRank(47951);
			player->LearnSpellHighestRank(48073);
			player->LearnSpellHighestRank(48078);
			player->LearnSpellHighestRank(48087);
			player->LearnSpellHighestRank(53023);
			player->LearnSpellHighestRank(48161);
			player->LearnSpellHighestRank(48066);
			player->LearnSpellHighestRank(48162);
			player->LearnSpellHighestRank(48074);
			player->LearnSpellHighestRank(48068);
			player->LearnSpellHighestRank(48158);
			player->LearnSpellHighestRank(48125);
		}
		void RogueSpells(Player* player)
		{
			player->LearnSpell(SPELL_BOWS, true);
			player->LearnSpell(SPELL_CROSSBOWS, true);
			player->LearnSpell(SPELL_DUAL_WIELD, true);
			player->LearnSpell(SPELL_FIST_WEAPONS, true);
			player->LearnSpell(SPELL_GUNS, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_SHOOT, true);
			player->LearnSpell(SPELL_THROW, true);
			player->LearnSpell(SPELL_THROWN, true);
			player->LearnSpellHighestRank(921);
			player->LearnSpellHighestRank(1776);
			player->LearnSpellHighestRank(1766);
			player->LearnSpellHighestRank(1804);
			player->LearnSpellHighestRank(51722);
			player->LearnSpellHighestRank(1725);
			player->LearnSpellHighestRank(2836);
			player->LearnSpellHighestRank(1833);
			player->LearnSpellHighestRank(1842);
			player->LearnSpellHighestRank(2094);
			player->LearnSpellHighestRank(1860);
			player->LearnSpellHighestRank(6774);
			player->LearnSpellHighestRank(26669);
			player->LearnSpellHighestRank(8643);
			player->LearnSpellHighestRank(11305);
			player->LearnSpellHighestRank(1787);
			player->LearnSpellHighestRank(26889);
			player->LearnSpellHighestRank(31224);
			player->LearnSpellHighestRank(5938);
			player->LearnSpellHighestRank(51724);
			player->LearnSpellHighestRank(57934);
			player->LearnSpellHighestRank(48674);
			player->LearnSpellHighestRank(48669);
			player->LearnSpellHighestRank(48659);
			player->LearnSpellHighestRank(48668);
			player->LearnSpellHighestRank(48672);
			player->LearnSpellHighestRank(48691);
			player->LearnSpellHighestRank(48657);
			player->LearnSpellHighestRank(57993);
			player->LearnSpellHighestRank(51723);
			player->LearnSpellHighestRank(48676);
			player->LearnSpellHighestRank(48638);
		}
		void ShamanSpells(Player* player)
		{
			if (player->GetTeam() == ALLIANCE)
			{
// heroism
				player->LearnSpellHighestRank(32182);
			}
			else
			{
// Bloodlust
				player->LearnSpellHighestRank(2825);
			}
			player->AddItem(46978, 1);
			player->LearnSpell(SPELL_BLOCK, true);
			player->LearnSpell(SPELL_FIST_WEAPONS, true);
			player->LearnSpell(SPELL_MAIL, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_RELIC_4, true);
			player->LearnSpell(SPELL_SHIELD, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
			player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
			player->LearnSpellHighestRank(30671);
			player->LearnSpellHighestRank(2484);
			player->LearnSpellHighestRank(526);
			player->LearnSpellHighestRank(57994);
			player->LearnSpellHighestRank(8143);
			player->LearnSpellHighestRank(2645);
			player->LearnSpellHighestRank(2870);
			player->LearnSpellHighestRank(8166);
			player->LearnSpellHighestRank(131);
			player->LearnSpellHighestRank(10399);
			player->LearnSpellHighestRank(6196);
			player->LearnSpellHighestRank(546);
			player->LearnSpellHighestRank(556);
			player->LearnSpellHighestRank(8177);
			player->LearnSpellHighestRank(20608);
			player->LearnSpellHighestRank(36936);
			player->LearnSpellHighestRank(8012);
			player->LearnSpellHighestRank(8512);
			player->LearnSpellHighestRank(6495);
			player->LearnSpellHighestRank(8170);
			player->LearnSpellHighestRank(3738);
			player->LearnSpellHighestRank(2062);
			player->LearnSpellHighestRank(2894);
			player->LearnSpellHighestRank(57960);
			player->LearnSpellHighestRank(49276);
			player->LearnSpellHighestRank(49236);
			player->LearnSpellHighestRank(58734);
			player->LearnSpellHighestRank(58582);
			player->LearnSpellHighestRank(58753);
			player->LearnSpellHighestRank(49231);
			player->LearnSpellHighestRank(49238);
			player->LearnSpellHighestRank(49277);
			player->LearnSpellHighestRank(55459);
			player->LearnSpellHighestRank(49271);
			player->LearnSpellHighestRank(49284);
			player->LearnSpellHighestRank(51994);
			player->LearnSpellHighestRank(61657);
			player->LearnSpellHighestRank(58739);
			player->LearnSpellHighestRank(49233);
			player->LearnSpellHighestRank(58656);
			player->LearnSpellHighestRank(58790);
			player->LearnSpellHighestRank(58745);
			player->LearnSpellHighestRank(58796);
			player->LearnSpellHighestRank(58757);
			player->LearnSpellHighestRank(49273);
			player->LearnSpellHighestRank(51514);
			player->LearnSpellHighestRank(60043);
			player->LearnSpellHighestRank(49281);
			player->LearnSpellHighestRank(58774);
			player->LearnSpellHighestRank(58749);
			player->LearnSpellHighestRank(58704);
			player->LearnSpellHighestRank(58643);
			player->LearnSpellHighestRank(58804);
		}
		void WarlockSpells(Player* player)
		{
			player->LearnSpell(SPELL_DAGGERS, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_SHOOT_WANDS, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_WANDS, true);
			player->LearnSpellHighestRank(59671);
			player->LearnSpellHighestRank(688);
			player->LearnSpellHighestRank(696);
			player->LearnSpellHighestRank(697);
			player->LearnSpellHighestRank(5697);
			player->LearnSpellHighestRank(698);
			player->LearnSpellHighestRank(712);
			player->LearnSpellHighestRank(126);
			player->LearnSpellHighestRank(5138);
			player->LearnSpellHighestRank(5500);
			player->LearnSpellHighestRank(132);
			player->LearnSpellHighestRank(691);
			player->LearnSpellHighestRank(18647);
			player->LearnSpellHighestRank(11719);
			player->LearnSpellHighestRank(1122);
			player->LearnSpellHighestRank(17928);
			player->LearnSpellHighestRank(6215);
			player->LearnSpellHighestRank(18540);
			player->LearnSpellHighestRank(23161);
			player->LearnSpellHighestRank(29858);
			player->LearnSpellHighestRank(50511);
			player->LearnSpellHighestRank(61191);
			player->LearnSpellHighestRank(47884);
			player->LearnSpellHighestRank(47856);
			player->LearnSpellHighestRank(47813);
			player->LearnSpellHighestRank(47855);
			player->LearnSpellHighestRank(47888);
			player->LearnSpellHighestRank(47865);
			player->LearnSpellHighestRank(47860);
			player->LearnSpellHighestRank(47857);
			player->LearnSpellHighestRank(47823);
			player->LearnSpellHighestRank(47891);
			player->LearnSpellHighestRank(47878);
			player->LearnSpellHighestRank(47864);
			player->LearnSpellHighestRank(57595);
			player->LearnSpellHighestRank(47893);
			player->LearnSpellHighestRank(47820);
			player->LearnSpellHighestRank(47815);
			player->LearnSpellHighestRank(47809);
			player->LearnSpellHighestRank(60220);
			player->LearnSpellHighestRank(47867);
			player->LearnSpellHighestRank(47889);
			player->LearnSpellHighestRank(48018);
			player->LearnSpellHighestRank(47811);
			player->LearnSpellHighestRank(47838);
			player->LearnSpellHighestRank(57946);
			player->LearnSpellHighestRank(58887);
			player->LearnSpellHighestRank(47836);
			player->LearnSpellHighestRank(61290);
			player->LearnSpellHighestRank(47825);
		}
		void WarriorSpells(Player* player)
		{
			player->LearnSpell(SPELL_BLOCK, true);
			player->LearnSpell(SPELL_BOWS, true);
			player->LearnSpell(SPELL_CROSSBOWS, true);
			player->LearnSpell(SPELL_DUAL_WIELD, true);
			player->LearnSpell(SPELL_FIST_WEAPONS, true);
			player->LearnSpell(SPELL_GUNS, true);
			player->LearnSpell(SPELL_ONE_HANDED_AXES, true);
			player->LearnSpell(SPELL_ONE_HANDED_MACES, true);
			player->LearnSpell(SPELL_ONE_HANDED_SWORDS, true);
			player->LearnSpell(SPELL_PLATE, true);
			player->LearnSpell(SPELL_POLEARMS, true);
			player->LearnSpell(SPELL_SHIELD, true);
			player->LearnSpell(SPELL_SHOOT, true);
			player->LearnSpell(SPELL_STAVES, true);
			player->LearnSpell(SPELL_THROW, true);
			player->LearnSpell(SPELL_THROWN, true);
			player->LearnSpell(SPELL_TWO_HANDED_AXES, true);
			player->LearnSpell(SPELL_TWO_HANDED_MACES, true);
			player->LearnSpell(SPELL_TWO_HANDED_SWORDS, true);
			player->LearnSpellHighestRank(2457);
			player->LearnSpellHighestRank(1715);
			player->LearnSpellHighestRank(2687);
			player->LearnSpellHighestRank(71);
			player->LearnSpellHighestRank(355);
			player->LearnSpellHighestRank(7384);
			player->LearnSpellHighestRank(72);
			player->LearnSpellHighestRank(694);
			player->LearnSpellHighestRank(2565);
			player->LearnSpellHighestRank(676);
			player->LearnSpellHighestRank(20230);
			player->LearnSpellHighestRank(12678);
			player->LearnSpellHighestRank(5246);
			player->LearnSpellHighestRank(1161);
			player->LearnSpellHighestRank(871);
			player->LearnSpellHighestRank(2458);
			player->LearnSpellHighestRank(20252);
			player->LearnSpellHighestRank(18449);
			player->LearnSpellHighestRank(1680);
			player->LearnSpellHighestRank(6552);
			player->LearnSpellHighestRank(11578);
			player->LearnSpellHighestRank(1719);
			player->LearnSpellHighestRank(34428);
			player->LearnSpellHighestRank(23920);
			player->LearnSpellHighestRank(3411);
			player->LearnSpellHighestRank(55694);
			player->LearnSpellHighestRank(47450);
			player->LearnSpellHighestRank(47465);
			player->LearnSpellHighestRank(47520);
			player->LearnSpellHighestRank(47467);
			player->LearnSpellHighestRank(47436);
			player->LearnSpellHighestRank(47502);
			player->LearnSpellHighestRank(47437);
			player->LearnSpellHighestRank(47475);
			player->LearnSpellHighestRank(47440);
			player->LearnSpellHighestRank(47471);
			player->LearnSpellHighestRank(57755);
			player->LearnSpellHighestRank(57823);
			player->LearnSpellHighestRank(47488);
		}
	};
	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_PromocionAI(creature);
	}
};
void AddSC_npc_promocion()
{
	new npc_promocion_gossip;
}
