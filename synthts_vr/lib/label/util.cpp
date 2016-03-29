#include <iostream>
#include "../etana/proof.h"
#include "util.h"


bool is_lvowel (CFSWString c) {
	if (c.FindOneOf(L"aeiouõäöüy") > -1)	return true;
		return false;
}

bool is_uvowel (CFSWString c) {
	if (c.FindOneOf(L"AEIOUÕÄÖÜY") > -1)	return true;
		return false;
}

bool is_lconsonant (CFSWString c) {
	if (c.FindOneOf(L"bcdfghjklmnpqrsšžtvwxz") > -1)	return true;
		return false;
}

bool is_uconsonant (CFSWString c) {
	if (c.FindOneOf(L"BCDFGHJKLMNPQRSŠŽTVWXZ") > -1) return true;
		return false;
}

bool is_ending (CFSWString c) {
	if (c.FindOneOf(L".?!;") > -1)	return true;
		return false;
}

bool is_tab (CFSWString c) {
	if (c.FindOneOf(L"\t\n") > -1)	return true;
		return false;
}

bool is_break (CFSWString c) {
	if (c.FindOneOf(L"\n") > -1)	return true;
		return false;
}

bool is_space (CFSWString c) {
	if (c.FindOneOf(sp) > -1)	return true;
		return false;
}

bool is_fchar (CFSWString c) {
	if (c.FindOneOf(L"ÀÁÂÃàáâãÈÉÊËèéêëÌÍÎÏŸÝìíîïÿýÒÓÔÅòóôåÙÚÛùúûæÆØŒøœñÑçÇßÐÞðþ") > -1)	return true;
		return false;
}

bool is_underscore (CFSWString c) { //liitsõna värk, selleks lahku
	if (c.FindOneOf(L"_") > -1)	return true;
		return false;
}

bool is_symbol (CFSWString c) {
	if ( (c.FindOneOf(L"-*@#€$£%&/\\=+~<>§αβγδ") > -1) || is_underscore(c)) 	return true;
		return false;
}

bool is_digit (CFSWString c) {
	if (c.FindOneOf(L"0123456789") > -1)	return true;
		return false;
}

bool is_colon (CFSWString c) {
	if (c.FindOneOf(L":") > -1)	return true;
		return false;
}

bool is_semicolon (CFSWString c) {
	if (c.FindOneOf(L";") > -1)	return true;
		return false;
}

bool is_comma (CFSWString c) {
	if (c.FindOneOf(L",") > -1)	return true;
		return false;
}

bool is_dash (CFSWString c) {
	if (c.FindOneOf(L"–") > -1)	return true;
		return false;
}

bool is_hyphen (CFSWString c) {
	if (c.FindOneOf(L"-") > -1)	return true;
		return false;
}

bool is_bbracket (CFSWString c) {
	if (c.FindOneOf(L"([{") > -1)	return true;
		return false;
}

bool is_ebracket (CFSWString c) {
	if (c.FindOneOf(L")]}") > -1)	return true;
		return false;
}

bool is_bhyphen (CFSWString c) {
	if (is_hyphen(c) || is_dash(c)) return true;
		return false;
}


bool is_whitespace (CFSWString c) {
	if (is_tab(c) || is_space(c)) return true;
		return false;
}

bool is_vowel (CFSWString c) {
	if (is_lvowel(c) || is_uvowel(c)) return true;
		return false;
}

bool is_consonant (CFSWString c) {
	if (is_lconsonant(c) || is_uconsonant(c))	return true;
		return false;
}

bool is_upper (CFSWString c) {
	if (is_uconsonant(c) || is_uvowel(c))	return true;
		return false;
}

bool is_char (CFSWString c) {
	if (is_vowel(c) || is_consonant(c) || c==L"'")	return true;
		return false;
}

bool is_conju (CFSWString c) {
	if (c == L"ja" || c == L"ning" || c == L"ega" || c == L"ehk" || c == L"või")	return true;
		return false;
}

bool is_compound_word (CFSWString c) {
		for (INTPTR i = 0; i < c.GetLength(); i++)
			if (is_underscore(c.GetAt(i))) return true;
		return false;
}

bool is_upper_word (CFSWString c) {
		for (INTPTR i = 0; i < c.GetLength(); i++)
			if (!is_upper(c.GetAt(i))) return false;
		return true;
}


bool is_fsymbol (CFSWString c) { //ainult tüübiarray jaoks
	if (is_symbol(c) || is_ending(c) || is_colon(c) || is_dash(c) || is_hyphen(c) || is_comma(c))	return true;
		return false;
}


bool has_vowel(CFSWString s) {
		for (INTPTR i = 0; i < s.GetLength(); i++)	{
			if (is_vowel(s.GetAt(i))) return true;
		}
		return false;
}

INTPTR ctype (CFSWString c) {
	if (is_char(c)) return 1;
		else
	if (is_fsymbol(c)) return 2;
	 else
	if (is_digit(c)) return 3;
	return 0;
}

void make_ctype_array (CFSWString s, CFSArray<CFSWString> &a) {
	for (INTPTR i = 0; i < s.GetLength(); i++)	{
		CFSWString c = s.GetAt(i);
		if (i == 0) {
			a.AddItem(c);
		}
		else {
			INTPTR arr_size = a.GetSize()-1;
			CFSWString lc = a[arr_size];
			lc = lc.GetAt(lc.GetLength()-1);
			if ( ctype(c) == ctype(lc) ) 
					a[arr_size] += c;			
				else 
					a.AddItem(c);
		}
	}
}

CFSWString make_char_string (CFSWString c) {
	CFSWString res;
	for (INTPTR i = 0; i < c.GetLength(); i++)	{
		if (is_char(c.GetAt(i))) res += c.GetAt(i);
	}		
	return res;
}


INTPTR explode(CFSWString s, CFSWString cSplitter, CFSArray<CFSWString> &Array) {
	Array.Cleanup();
	INTPTR ipStart=0;
	for (INTPTR ip=0; ip<s.GetLength(); ip++){
		if (s.GetAt(ip)==cSplitter){
			Array.AddItem(s.Mid(ipStart, ip-ipStart));
			ipStart=ip+1;
		}
		else
		if (cSplitter.GetLength() == 0)
			Array.AddItem(s.GetAt(ip));
	}
	if (cSplitter.GetLength() > 0) 
		Array.AddItem(s.Mid(ipStart));
	return Array.GetSize();
}


CMorphInfo clean_anaroot_output (CMorphInfo MI) {
	CFSWString s;
	for (INTPTR i=0; i < MI.m_szRoot.GetLength(); i++) {
		if (MI.m_szRoot.GetAt(i) != L'=') s += MI.m_szRoot.GetAt(i);
	}	
	MI.m_szRoot = s;
	return MI;
}




const char* ccstr (CFSWString s) {
    return FSStrWtoA(s, FSCP_UTF8);
}


INTPTR is_abbreviation(CFSWString s, CFSArray<CFSWString> &a) {
    // Lühendid EKRst
    if (s.GetAt(s.GetLength() - 1) == L'.') s.Delete(s.GetLength() - 1, 1);
    if (s == L"ak") return explode(L"arvelduskonto", sp, a);
    if (s == L"aotl") return explode(L"aotlinõ", sp, a);
    if (s == L"apr") return explode(L"april'", sp, a);
    if (s == L"AS") return explode(L"aktsiaselts'", sp, a);
    if (s == L"aug") return explode(L"august'", sp, a);
    if (s == L"aü") return explode(L"ammõdiütisüs", sp, a);
    if (s == L"dets") return explode(L"detsembri", sp, a);
    if (s == L"dl") return explode(L"dessert’luidsatäüs'", sp, a);
    if (s == L"dots") return explode(L"dotsent'", sp, a);
    if (s == L"dr") return explode(L"doktor'", sp, a);
    if (s == L"e") return explode(L"ehk", sp, a);
    if (s == L"EL") return explode(L"Euruupa Liit", sp, a);
    if (s == L"i.m.a") return explode(L"inne miiq aigo", sp, a);
    if (s == L"iKr") return explode(L"inne Kristust", sp, a);
    if (s == L"inn") return explode(L"inneskine", sp, a);
    if (s == L"FIE") return explode(L"füüsilidsest inemisest ettevõtja", sp, a);
    if (s == L"hr") return explode(L"herr", sp, a);
    if (s == L"hrl") return explode(L"hariligult", sp, a);
    if (s == L"I") return explode(L"iispäiv", sp, a);
    if (s == L"ik") return explode(L"isikukood", sp, a);
    if (s == L"ins") return explode(L"insinüür'", sp, a);
    if (s == L"it") return explode(L"infoteknoloogia", sp, a);
    if (s == L"IT") return explode(L"infoteknoloogia", sp, a);
    if (s == L"j.a") return explode(L"juures asuv", sp, a);
    if (s == L"jaan") return explode(L"jaanuaar'", sp, a);
    if (s == L"jj") return explode(L"ja järg'mäne", sp, a);
    if (s == L"jm") return explode(L"ja muuq", sp, a);
    if (s == L"jms") return explode(L"ja muuq sääntseq", sp, a);
    if (s == L"jmt") return explode(L"ja mitmõq tõõsõq", sp, a);
    if (s == L"jn") return explode(L"joonis", sp, a);
    if (s == L"jne") return explode(L"ja nii edesi", sp, a);
    if (s == L"jpt") return explode(L"ja pall'oq tõõsõq", sp, a);
    if (s == L"jr") return explode(L"juunior'", sp, a);
    if (s == L"jrk") return explode(L"järekõrd", sp, a);
    if (s == L"jsk") return explode(L"jaoskund", sp, a);
    if (s == L"jt") return explode(L"ja tõõsõq", sp, a);
    if (s == L"juh") return explode(L"juhataja", sp, a);
    if (s == L"jun") return explode(L"juunior'", sp, a);
    if (s == L"jv") return explode(L"järv'", sp, a);
    if (s == L"K") return explode(L"kolmapäiv", sp, a);
    if (s == L"kd") return explode(L"köüdeq", sp, a);
    if (s == L"khk") return explode(L"kihlkund", sp, a);
    if (s == L"kk") return explode(L"keskkuul'", sp, a);
    if (s == L"kl") return explode(L"kell", sp, a);
    if (s == L"knd") return explode(L"kandidaat'", sp, a);
    if (s == L"kod") return explode(L"kodanik", sp, a);
    if (s == L"kpl") return explode(L"kauplus", sp, a);
    if (s == L"kq") return explode(L"kaeq", sp, a);
    if (s == L"kr") return explode(L"kruun'", sp, a);
    if (s == L"kt") return explode(L"kohusõtäütjä", sp, a);
    if (s == L"kub") return explode(L"kubõrmang", sp, a);
    if (s == L"kv") return explode(L"kvartal'", sp, a);
    if (s == L"KÜ") return explode(L"kortinaütistü", sp, a);
    if (s == L"l") return explode(L"liitri", sp, a);
    if (s == L"Pu") return explode(L"puul'päiv", sp, a);
    if (s == L"lg") return explode(L"lõigõq", sp, a);
    if (s == L"lj") return explode(L"liinajago", sp, a);
    if (s == L"lk") return explode(L"lehekülg'", sp, a);
    if (s == L"LK") return explode(L"luuduskaitsõ all", sp, a);
    if (s == L"lm") return explode(L"liidumaa", sp, a);
    if (s == L"lo") return explode(L"liinaosa", sp, a);
    if (s == L"lp") return explode(L"lugupeet", sp, a);
    if (s == L"lüh") return explode(L"lühkümbähe", sp, a);
    if (s == L"M") return explode(L"mehile", sp, a);
    if (s == L"mag") return explode(L"magistri", sp, a);
    if (s == L"m.a.p") return explode(L"miiq aoarvamisõ perrä ", sp, a);
    if (s == L"min") return explode(L"minot'", sp, a);
    if (s == L"mk") return explode(L"maakund", sp, a);
    if (s == L"mld") return explode(L"mill'ard'", sp, a);
    if (s == L"mln") return explode(L"mill'on'", sp, a);
    if (s == L"mnt") return explode(L"maantii", sp, a);
    if (s == L"mob") return explode(L"mobiil’telefon’", sp, a);
    if (s == L"ms") return explode(L"muusiän", sp, a);
    if (s == L"MTÜ") return explode(L"mittetulosaamisütisüs", sp, a);
    if (s == L"N") return explode(L"neläpäiv", sp, a);
    if (s == L"nim") return explode(L"nimeline", sp, a);
    if (s == L"nn") return explode(L"niinimitet", sp, a);
    if (s == L"nov") return explode(L"novvembri", sp, a);
    if (s == L"nr") return explode(L"nummõr’", sp, a);
    if (s == L"nt") return explode(L"näütüses", sp, a);
    if (s == L"nü") return explode(L"nii üteldäq", sp, a);
    if (s == L"okt") return explode(L"oktoobri", sp, a);
    if (s == L"oa") return explode(L"opiaastak", sp, a);
    if (s == L"op") return explode(L"oppaja", sp, a);
    if (s == L"osk") return explode(L"osakund", sp, a);
    if (s == L"OÜ") return explode(L"osaütisüs", sp, a);
    if (s == L"P") return explode(L"pühäpäiv", sp, a);
    if (s == L"pa") return explode(L"puul’aastak", sp, a);
    if (s == L"pk") return explode(L"post’kast’", sp, a);
    if (s == L"pKr") return explode(L"perän Kristusõ sündümist", sp, a);
    if (s == L"pms") return explode(L"päämädselt", sp, a);
    if (s == L"p.o") return explode(L"piät olõma", sp, a);
    if (s == L"pr") return explode(L"provva", sp, a);
    if (s == L"prl") return explode(L"preili", sp, a);
    if (s == L"prof") return explode(L"profesri", sp, a);
    if (s == L"ps") return explode(L"puul’saar’", sp, a);
    if (s == L"pst") return explode(L"puiõstii", sp, a);
    if (s == L"ptk") return explode(L"päätükk", sp, a);
    if (s == L"R") return explode(L"riidi", sp, a);
    if (s == L"raj") return explode(L"rajuun’", sp, a);
    if (s == L"rbl") return explode(L"ruubli", sp, a);
    if (s == L"RE") return explode(L"riigiettevõtõq", sp, a);
    if (s == L"reg") return explode(L"registriir’mis", sp, a);
    if (s == L"rg") return explode(L"registri", sp, a);
    if (s == L"rmdk") return explode(L"raamadukogo", sp, a);
    if (s == L"rkl") return explode(L"riigikogoliigõq", sp, a);
    if (s == L"rtj") return explode(L"raudtiijaam", sp, a);
    if (s == L"s") return explode(L"sekond’", sp, a);
    if (s == L"SA") return explode(L"siht’asotus", sp, a);
    if (s == L"s.a") return explode(L"seo aastaga", sp, a);
    if (s == L"saj") return explode(L"sajand", sp, a);
    if (s == L"sh") return explode(L"säälhulgan", sp, a);
    if (s == L"sen") return explode(L"seenior’", sp, a);
    if (s == L"sept") return explode(L"septembri", sp, a);
    if (s == L"skp") return explode(L"seo kuu pääväl", sp, a);
    if (s == L"spl") return explode(L"supiluidsatäüs’", sp, a);
    if (s == L"sl") return explode(L"supiluidsatäüs’", sp, a);
    if (s == L"sm") return explode(L"seldsimiis’", sp, a);
    if (s == L"s.o") return explode(L"seo om", sp, a);
    if (s == L"s.t") return explode(L"seo tähendäs", sp, a);
    if (s == L"st") return explode(L"seo tähendäs", sp, a);
    if (s == L"stj") return explode(L"saatja", sp, a);
    if (s == L"srn") return explode(L"surnud", sp, a);
    if (s == L"sü") return explode(L"säilitusüksus", sp, a);
    if (s == L"snd") return explode(L"sündünüq", sp, a);
    if (s == L"t") return explode(L"tonn’", sp, a);
    if (s == L"T") return explode(L"tõõsõpäiv", sp, a);
    if (s == L"tehn") return explode(L"tehniline", sp, a);
    if (s == L"tel") return explode(L"telefon’", sp, a);
    if (s == L"tk") return explode(L"tükk(ü)", sp, a);
    if (s == L"tl") return explode(L"tiiluidsatäüs", sp, a);
    if (s == L"tlk") return explode(L"tõlkja", sp, a);
    if (s == L"Tln") return explode(L"Talliin", sp, a);
    if (s == L"tn") return explode(L"tänav", sp, a);
    if (s == L"tr") return explode(L"trükk", sp, a);
    if (s == L"Trt") return explode(L"Tarto", sp, a);
    if (s == L"tv") return explode(L"televisiuun’", sp, a);
    if (s == L"TV") return explode(L"televisiuun’", sp, a);
    if (s == L"u") return explode(L"umbõs", sp, a);
    if (s == L"ukj") return explode(L"uue kalendri järgi", sp, a);
    if (s == L"UÜ") return explode(L"usaldusütisüs", sp, a);
    if (s == L"v") return explode(L"vai", sp, a);
    if (s == L"v.a") return explode(L"vällä arvat", sp, a);
    if (s == L"van") return explode(L"vanaaaolinõ", sp, a);
    if (s == L"VE") return explode(L"väikuettevõtõq", sp, a);
    if (s == L"veebr") return explode(L"veebruaar’", sp, a);
    if (s == L"vkj") return explode(L"vana kalendri järgi", sp, a);
    if (s == L"vm") return explode(L"vai muu(d)", sp, a);
    if (s == L"vms") return explode(L"vai muu sääne", sp, a);
    if (s == L"vrd") return explode(L"võrdlõq", sp, a);
    if (s == L"ÕL") return explode(L"Õuruupa Liit", sp, a);
    if (s == L"õpil") return explode(L"õpilane", sp, a);
    if (s == L"ÄÜ") return explode(L"äriütisüs", sp, a);
    if (s == L"ü.a") return explode(L"üten arvat", sp, a);
    if (s == L"ÜE") return explode(L"ütisettevõtõq", sp, a);
    if (s == L"SEK") return explode(L"Roodsi kruuni", sp, a);
    if (s == L"NOK") return explode(L"Norra kruuni", sp, a);
    if (s == L"RUR") return explode(L"Vinne ruublit", sp, a);
    if (s == L"USD") return explode(L"USA dollarit", sp, a);
    if (s == L"GBP") return explode(L"Inglüse nakla", sp, a);
    if (s == L"LVL") return explode(L"Läti latti", sp, a);
    if (s == L"LTL") return explode(L"Leedu litti", sp, a);
    if (s == L"EEK") return explode(L"Eesti kruuni", sp, a);
    return 0;
}


CFSWString replace_fchar (CFSWString c) {
	if (c == L"À") return L"a";
	if (c == L"Á") return L"a";
	if (c == L"Â") return L"a";
	if (c == L"Ã") return L"a";
	if (c == L"à") return L"a";
	if (c == L"á") return L"a";
	if (c == L"â") return L"a";
	if (c == L"ã") return L"a";
	if (c == L"È") return L"e";
	if (c == L"É") return L"e";
	if (c == L"Ê") return L"e";
	if (c == L"Ë") return L"e";
	if (c == L"è") return L"e";
	if (c == L"é") return L"e";
	if (c == L"ê") return L"e";
	if (c == L"ë") return L"e";
	if (c == L"Ì") return L"i";
	if (c == L"Í") return L"i";
	if (c == L"Î") return L"i";
	if (c == L"Ï") return L"i";
	if (c == L"Ÿ") return L"i";
	if (c == L"Ý") return L"i";
	if (c == L"ì") return L"i";
	if (c == L"í") return L"i";
	if (c == L"î") return L"i";
	if (c == L"ï") return L"i";
	if (c == L"ÿ") return L"ü";
	if (c == L"ý") return L"ü";
	if (c == L"Ò") return L"o";
	if (c == L"Ó") return L"o";
	if (c == L"Ô") return L"o";
	if (c == L"Å") return L"o";
	if (c == L"ò") return L"o";
	if (c == L"ó") return L"o";
	if (c == L"ô") return L"o";
	if (c == L"å") return L"o";
	if (c == L"Ù") return L"u";
	if (c == L"Ú") return L"u";
	if (c == L"Û") return L"u";
	if (c == L"ù") return L"u";
	if (c == L"ú") return L"u";
	if (c == L"û") return L"u";
	if (c == L"æ") return L"ä";
	if (c == L"Æ") return L"ä";
	if (c == L"Ø") return L"ö";
	if (c == L"Œ") return L"ö";
	if (c == L"ø") return L"ö";
	if (c == L"œ") return L"ö";
	if (c == L"ñ") return L"n";
	if (c == L"Ñ") return L"n";
	if (c == L"ç") return L"s";
	if (c == L"Ç") return L"s";
	if (c == L"ß") return L"s";
	if (c == L"Ð") return L"k";
	if (c == L"Þ") return L"k";
	if (c == L"ð") return L"k";
	if (c == L"þ") return L"k";	
        

}

CFSWString replace_schar (CFSWString c) {
    c = c.ToLower();
    if (c == L"a") return L"aa";
    if (c == L"b") return L"bee";
    if (c == L"c") return L"tsee";
    if (c == L"d") return L"dee";
    if (c == L"e") return L"ee";
    if (c == L"f") return L"eff’";
    if (c == L"g") return L"gee";
    if (c == L"h") return L"haa";
    if (c == L"i") return L"ii";
    if (c == L"j") return L"jott’";
    if (c == L"k") return L"kaa";
    if (c == L"l") return L"ell’";
    if (c == L"m") return L"emm’";
    if (c == L"n") return L"enn’";
    if (c == L"o") return L"oo";
    if (c == L"p") return L"pee";
    if (c == L"q") return L"hõq";
    if (c == L"r") return L"err’";
    if (c == L"s") return L"ess’";
    if (c == L"š") return L"saa";
    if (c == L"ž") return L"see";
    if (c == L"t") return L"tee";
    if (c == L"u") return L"uu";
    if (c == L"v") return L"vee";
    if (c == L"w") return L"katsisvee";
    if (c == L"õ") return L"õõ";
    if (c == L"ä") return L"ää";
    if (c == L"ö") return L"öö";
    if (c == L"ü") return L"üü";
    if (c == L"x") return L"iks’";
    if (c == L"y") return L"igrek’";
    if (c == L"z") return L"tsett’";
    if (c == L".") return L"punkt’";
    if (c == L",") return L"koma";
    if (c == L":") return L"katsispunkt’";
    if (c == L";") return L"punkt’koma";
    if (c == L"-") return L"kriips";
    if (c == L"_") return L"allkriips";
    if (c == L"*") return L"tärn’";
    if (c == L"!") return L"hõikamismärk’";
    if (c == L"?") return L"küsümismärk’";
    if (c == L"@") return L"ätt’";
    if (c == L"#") return L"trelliq";
    if (c == L"€") return L"õurot";
    if (c == L"$") return L"dollarit";
    if (c == L"£") return L"nakla";
    if (c == L"%") return L"protsenti";
    if (c == L"&") return L"änd’";
    if (c == L"/") return L"kaldkriips";
    if (c == L"\\") return L"taasperi kaldkriips";    
    if (c == L"=") return L"om võrdnõ";
    if (c == L"+") return L"pluss’";
    if (c == L"~") return L"lainõq";
    if (c == L"<") return L"suurõmb kuq";
    if (c == L">") return L"vähämb kuq";
    if (c == L"§") return L"paragraaf’";
    if (c == L"(") return L"klambridõ seen";
    if (c == L"[") return L"nulkklambridõ seen";
    if (c == L"{") return L"loogõliidsi klambridõ seen";
    if (c == L"α") return L"al’fa";
    if (c == L"β") return L"beeta";
    if (c == L"γ") return L"gamma";
    if (c == L"δ") return L"delta";
    
    return L"tundmatumärk";
}































