#include "server.h"
#include "include/Hexdump.hpp"

#pragma warning(disable : 4996)


int custom_length(const char s[])
{
	for (int i = 0; ; i++)
		if (s[i] == 'm' && s[i + 1] == 'y' && s[i + 2] == 'c' && s[i + 3] == 's' && s[i + 4] == 't' && s[i + 5] == 'm' && s[i + 6] == '0' && s[i + 7] == 't' && s[i + 8] == 'r' && s[i + 9] == 'm' && s[i + 10] == 'n' && s[i + 11] == 't' && s[i + 12] == 'r')
			return i;
}

int set_response(char msg[], const char response[])
{
	int length = custom_length(response);
	copy(&response[0],	&response[length - 1], &msg[0]);
	return length;
}

bool msg_check(char msg[], const char s[], int offset = 0)
{
	if (custom_length(s) + offset > sizeof(msg))
		return false;

	for (int i = 0; i < custom_length(s); i++)
	{
		if (msg[i + offset] != s[i])
			return false;
	}
	return true;
}

int  server_response(char msg[], int length)
{
	int response = 0;
	cout << Hexdump(msg, length) << endl;

	if (msg_check(msg, "\x03" "mycstm0trmntr", 6))
 		response = set_response(msg, "\x1e\x00\x00\x00\x0c\x00\x01\x00\x08\x01\x12\x08\n\x06" "2551862" "\x06" "2551868" "\x04" "mycstm0trmntr");

	if (msg_check(msg, "\x04" "mycstm0trmntr", 6))
		response = set_response(msg, "\x08\x00\x00\x00\x02\x00\x00\x00" "mycstm0trmntr");

	if (msg_check(msg, "\x05" "mycstm0trmntr", 6))
		response = set_response(msg, "\x8b\x0b\x00\x00\x12\x00\x00\x00\x08\x02\x10\x01\x1a\xab\r\n\x06" "554396" "\x12\x18\n\x08" "g Server" "\x12\x0c" "Wizard#77714" "\x1a" "3DesignDataPlayerCharacter:Id_PlayerCharacter_Wizard " "\x88\xd7\xf8\xbe\xe2" "0(" "\x01" "0" "\x01" "8" "\xf8\xa8\x94\xbd\xe3" "0B" "\xcf\x01\x08\xe4\xb8\x80\xca\xd4\xbc\x05\x12" "!DesignDataItem:Id_Item_Torch_0001" "\x18\x03 \x03(\x08" "JN" "\n" "JDesignDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\r" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xf6\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xcb\x01\x08\xe0\xb8\x80\xca\xd4\xbc\x05\x12" "&DesignDataItem:Id_Item_ClothPants_0001" "\x18\x01 \x03" "(" "\x04" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x08" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\x95\x02\x08\xe2\xb8\x80\xca\xd4\xbc\x05\x12" "%DesignDataItem:Id_Item_WizardHat_0001" "\x18\x01 \x03" "(" "\x01" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x05" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\x05" "B" "\x8a\x01\x08\xdc\xb8\x80\xca\xd4\xbc\x05\x12" ",DesignDataItem:Id_Item_ProtectionPotion_0001" "\x18\x01 \x03" "(" "\x0e" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xec\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xd5\x01\x08\xde\xb8\x80\xca\xd4\xbc\x05\x12" "'DesignDataItem:Id_Item_WizardStaff_0001" "\x18\x01 \x03" "(" "\n" "JN" "\n" "JDesig" "mycstm0trmntr");

	if (msg_check(msg, "\x06" "mycstm0trmntr", 6))
		response = set_response(msg, "nDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\x13" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xec\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\x8e\x02\x08\xd8\xb8\x80\xca\xd4\xbc\x05\x12" "'DesignDataItem:Id_Item_WizardShoes_0001" "\x18\x01 \x03" "(" "\x05" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x01" "JC" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\x05" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\n" "B" "\x91\x02\x08\xda\xb8\x80\xca\xd4\xbc\x05\x12" "!DesignDataItem:Id_Item_Frock_0001" "\x18\x01 \x03" "(" "\x02" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x0f" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\x14\x1a\xce\t\n\x07" "3058778" "\x12\x1a\n\x08" "Emulator" "\x12\x0e" "Fighter#603620" "\x1a" "4DesignDataPlayerCharacter:Id_PlayerCharacter_Fighter " "\xa8\xd8\x82\xbc\xe3" "0(" "\x01" "0" "\x01" "8" "\xa8\xd8\x82\xbc\xe3" "0B" "\x97\x02\x08\xe6\xb8\x80\xca\xd4\xbc\x05\x12" "'DesignDataItem:Id_Item_PaddedTunic_0001" "\x18\x01 \x03" "(" "\x02" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\n" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "JI" "\n" "EDes" "mycstm0trmntr");

	if (msg_check(msg, "\x07" "mycstm0trmntr", 6))
		response = set_response(msg, "ignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\n" "B" "\xcf\x01\x08\xec\xb8\x80\xca\xd4\xbc\x05\x12" "!DesignDataItem:Id_Item_Torch_0001" "\x18\x03 \x03" "(" "\x08" "JN" "\n" "JDesignDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\r" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xf6\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xcb\x01\x08\xee\xb8\x80\xca\xd4\xbc\x05\x12" "&DesignDataItem:Id_Item_ClothPants_0001" "\x18\x01 \x03" "(" "\x04" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x08" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xcc\x01\x08\xe8\xb8\x80\xca\xd4\xbc\x05\x12" "'DesignDataItem:Id_Item_RoundShield_0001" "\x18\x01 \x03" "(" "\x0b" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\r" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xf4\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xd5\x01\x08\xea\xb8\x80\xca\xd4\xbc\x05\x12" "'DesignDataItem:Id_Item_ArmingSword_0001" "\x18\x01 \x03" "(" "\n" "JN" "\n" "JDesignDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\x16" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xec\xff\xff\xff\xff\xff\xff\xff\xff\x01\x08\x00\x00\x00\x02\x00\x00\x00\x08\x00\x00\x00\x02\x00\x00\x00" "mycstm0trmntr");

	if (msg_check(msg, "\x08" "554396" "mycstm0trmntr", 6))
		response = set_response(msg, "\x08\x00\x00\x00\x02\x00\x00\x00"  "mycstm0trmntr");
	
	if (msg_check(msg, "\n" "mycstm0trmntr", 6))
		response = set_response(msg, "\xb2\x06\x00\x00" "," "\x00\x00\x00\x08\x01\x12\xa5\r\n\x06" "255186" "\x12\x18\n\x08" "g Server" "\x12\x0c" "Wizard#77714" "\x1a" "3DesignDataPlayerCharacter:Id_PlayerCharacter_Wizard\"" "\x06" "554396(" "\x01" "0" "\x01" "B" "\x8e\x02\x08\xda\xff\xfd\xc5\xd4\xbc\x05\x12\'" "DesignDataItem:Id_Item_WizardShoes_0001" "\x18\x01 \x03" "(" "\x05" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x01" "JC" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\x05" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\n" "B" "\x91\x02\x08\xd8\xff\xfd\xc5\xd4\xbc\x05\x12" "!DesignDataItem:Id_Item_Frock_0001" "\x18\x01 \x03" "(" "\x02" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x0f" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\x14" "B" "\x8a\x01\x08\xde\xff\xfd\xc5\xd4\xbc\x05\x12" ",DesignDataItem:Id_Item_ProtectionPotion_0001" "\x18\x01 \x03" "(" "\x0e" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xec\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xd5\x01\x08\xdc\xff\xfd\xc5\xd4\xbc\x05\x12\'" "DesignDataItem:Id_Item_WizardStaff_0001" "\x18\x01 \x03" "(" "\n" "JN" "\n" "JDesignDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\x13" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xec\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\xcb\x01\x08\xd2\xff" "mycstm0trmntr");

	if (msg_check(msg, "\x0b" "mycstm0trmntr", 6))
		response = set_response(msg, "\xfd\xc5\xd4\xbc\x05\x12" "&DesignDataItem:Id_Item_ClothPants_0001" "\x18\x01 \x03" "(" "\x04" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x08" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "B" "\x95\x02\x08\xd6\xff\xfd\xc5\xd4\xbc\x05\x12" "%DesignDataItem:Id_Item_WizardHat_0001" "\x18\x01 \x03" "(" "\x01" "JE" "\n" "ADesignDataItemPropertyType:Id_ItemPropertyType_Effect_ArmorRating" "\x10\x05" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xfb\xff\xff\xff\xff\xff\xff\xff\xff\x01" "JI" "\n" "EDesignDataItemPropertyType:Id_ItemPropertyType_Effect_MagicRegistance" "\x10\x05" "B" "\xcf\x01\x08\xd4\xff\xfd\xc5\xd4\xbc\x05\x12" "!DesignDataItem:Id_Item_Torch_0001" "\x18\x03 \x03" "(" "\x08" "JN" "\n" "JDesignDataItemPropertyType:Id_ItemPropertyType_Effect_PhysicalWeaponDamage" "\x10\r" "JL" "\n" "?DesignDataItemPropertyType:Id_ItemPropertyType_Effect_MoveSpeed" "\x10\xf6\xff\xff\xff\xff\xff\xff\xff\xff\x01\x12\x00\x00\x00\x16\x00\x00\x00\x08\x01\x12\x06" "255186" "\x0c\x00\x00\x00" "5" "\x00\x00\x01\n\x02\x08\x01\x08\x00\x00\x00\x02\x00\x00\x00" "mycstm0trmntr");

	if (msg_check(msg, "\x08\x00\x00\x00\x1e" "'" "\x0c\x00" "mycstm0trmntr"))
		response = set_response(msg, "\x08\x00\x00\x00\x02\x00\x00\x00" "mycstm0trmntr");

	if (msg_check(msg, "\x08\x00\x00\x00" "/" "\t\r\x00" "mycstm0trmntr"))
		response = set_response(msg, "\x08\x00\x00\x00\x02\x00\x00\x00" "mycstm0trmntr");

	if (length > 11)
		if (msg[8] == '\x0a' && msg[9] == '\xd4' && msg[10] == '\x03') // steam authentication
			response = set_response(msg, "L" "\x00\x00\x00" "B'" "\x00\x01\n\x05\x08\x08\x10\x90" "N" "\n\x05\x08\x08\x10\x90" "N" "\n\x05\x08\x03\x10\xe8\x07\n\x04\x08\x07\x10" "d" "\n\x05\x08\x01\x10\xc8\x01\n\x05\x08\x02\x10\x90" "N" "\n\x05\x08\x05\x10\xf4\x03\n\x04\x08\x04\x10" "2" "\n\x05\x08\x08\x10\xe8\x07\n\x05\x08\x06\x10\xf4\x03" "mycstm0trmntr");
	
	cout << Hexdump(msg, response) << endl;
	cout << "---------------------------------------------------------------------------" << endl << endl;
	return response;
}