#include "../etana/proof.h"
#include "util.h"


bool can_palat(CFSWString c) {
    if (c.FindOneOf(L"BDFGHKLMNPRSTV") > -1) return true;
    return false;
}
CFSWString chars_to_phones_part_I(CFSWString &s) {
    CFSWString res;
    for (INTPTR i = 0; i < s.GetLength(); i++) {
        CFSWString c = s.GetAt(i);
        if (c == L']') {
            CFSWString t = CFSWString(s.GetAt(i - 1)).ToUpper();
            res.SetAt(res.GetLength() - 1, t.GetAt(0));
            //vaatab taha; pole kindel, et kas on vajalik
            t = CFSWString(s.GetAt(i - 2)).ToUpper();
            if (can_palat(t)) {
                res.SetAt(res.GetLength() - 2, t.GetAt(0));
                t = CFSWString(s.GetAt(i - 3)).ToUpper();
                if (can_palat(t)) {
                    res.SetAt(res.GetLength() - 2, t.GetAt(0));
                }
            }
            //vaatab ette					
            t = CFSWString(s.GetAt(i + 1)).ToUpper();
            if (can_palat(t)) {
                s.SetAt(i + 1, t.GetAt(0));
                t = CFSWString(s.GetAt(i + 2)).ToUpper();
                if (can_palat(t)) {
                    s.SetAt(i + 2, t.GetAt(0));
                }
            }
        } else
            if (c == L'<') {
            CFSWString t = CFSWString(s.GetAt(i + 1)).ToUpper();
            s.SetAt(i + 1, t.GetAt(0));
        } else
            if (c == L'?') {
        }//Ebanormaalne rõhk. Pärast vaatab, mis teha
        else
            if (c == L'x') res += L"ks";
        else
            if (c == L'y') res += L"i";
        else
            if (c == L'w') res += L"v";
        else
            if (c == L'z') res += L"ts";
        else
            if (c == L'c') {
            res += L"k";
        } else
            if (c == L'ü' && is_vowel(s.GetAt(i + 1)) && s.GetAt(i - 1) == L'ü')
            res += L"i";
        else
            res += c;
    }
    return res;
}

CFSWString syllabify2(CFSWString s) {
    CFSWString res;

    for (INTPTR i = 0; i < s.GetLength(); i++) {
        CFSWString c = s.GetAt(i);
        if (is_consonant(c) && is_vowel(s.GetAt(i - 1)) && is_vowel(s.GetAt(i + 1)))
            res += d;
        if (is_vowel(c) && is_vowel(s.GetAt(i - 1)) && is_vowel(s.GetAt(i + 1)) && c.ToLower() == s.GetAt(i + 1))
            res += d;
        if (is_consonant(c) && is_consonant(s.GetAt(i - 1)) && is_vowel(s.GetAt(i + 1)) && has_vowel(res)) //küsitav
            res += d;
        res += c;
    }
    return res;
}

CFSWString word_to_syls(CFSWString word) {
    word = chars_to_phones_part_I(word);
    CFSWString s = make_char_string(word);
    s = syllabify2(s);
    return s;
}

bool is_stressed_syl(CFSWString syl) {
    bool res = false;
    for (INTPTR i = 0; i < syl.GetLength(); i++) {
        if ((syl.GetAt(i) == colon) || ((is_vowel(syl.GetAt(i))) && (is_vowel(syl.GetAt(i + 1)))))
            res = true;
    }
    return res;
}


INTPTR extra_stress(CFSArray<syl_struct> &sv, INTPTR size) {
    if (size == 1) return 0;
    else
        for (INTPTR i = 1; i < size; i++)
            for (INTPTR i1 = 0; i1 < sv[i].syl.GetLength(); i1++) {
                if (sv[i].syl.GetAt(i1) == colon) return i;
                if (i1 > 0)
                    if (is_vowel(sv[i].syl.GetAt(i1)) && is_vowel(sv[i].syl.GetAt(i1 - 1)))
                        return i;
            }
    return 0;
}

void add_stress2(CFSArray<syl_struct> &sv, INTPTR wp) {
    /* Kõige radikaalsem rõhutus siiani. 
     * wp = kui on liitsõna esimene liige siis on seal pearõhk.
     */
    INTPTR main_stress = 2;
    INTPTR stress = 1;
    INTPTR size = sv.GetSize();
    INTPTR stress_type = extra_stress(sv, size);
    if (stress_type == 0) {
        for (INTPTR i = 0; i < size; i++) {
            if (i % 2 == 0) {
                if ((i == 0) && (wp == 0))
                    sv[i].stress = main_stress;
                else
                    sv[i].stress = stress;
            }
        }
        if (size > 1) sv[size - 1].stress = 0;
    }
    else {
        if (wp == 0)
            sv[stress_type].stress = main_stress;
        else
            sv[stress_type].stress = stress;

        //esimene pool
        if (stress_type == 1) sv[0].stress = 0;
        else
            for (INTPTR i = stress_type - 1; i >= 0; i--)
                if (i % 2 == 0)
                    sv[i].stress = stress;

        if ((stress_type % 2 != 0) && (stress_type > 1))
            sv[stress_type - 1].stress = 0;

        //teine pool

        INTPTR lopp = size - stress_type;

        if (lopp > 3) {
            for (INTPTR i = stress_type + 1; i < size; i++)
                if (i % 2 != 0) sv[i].stress = stress;

            sv[size - 1].stress = 0;
        }
    }
}


bool must (CFSWString c) {
	if (c.FindOneOf(L"eijäöü") > -1)	return true;
		return false;
}

bool can_palat_vr(CFSWString c) {
    if (c.FindOneOf(L"bdfghklmnprstv") > -1) return true;
    return false;
}



CFSWString palat_vru (CFSWString s) {
    CFSWString res;
    bool m = false;
    if (s == L"är'") res = L"ärq"; 
    else
    if (s == L"ar'") res = L"arq"; 
    else
    if (s == L"jäl'") res = L"jälq"; 
    else
    if (s == L"jal'") res = L"jalq"; 
    else
    if (s == L"kül'") res = L"külq"; 
    else
    if (s == L"pan'") res = L"panq"; 
    else
    if (s == L"tul'") res = L"tulq"; 
    else
    if (s == L"ol'") res = L"olq"; 
    else
        for (INTPTR i = s.GetLength()-1; i >= 0; i--) {
        CFSWString c = s.GetAt(i);
        if (c == L"'") {
            m = true;
        } else 
            if (must(c)) {
                res = c + res;
                m = true;
            }
            else
        if (m) {
            if (can_palat_vr(c)) {
                c = c.ToUpper();
                res = c + res;
            } else {
                res = c + res;
                m = false;
            }
        } else {
            res = c + res;
        }
        
       
    }    
    return res;
}


void do_syls(word_struct &w) {
    CFSArray<syl_struct> sv, sv_temp;
    syl_struct ss;
    CFSArray<CFSWString> temp_arr, c_words;
    ss.phone_c = 0, ss.word_p = 0, ss.phr_p = 0, ss.utt_p = 0;
    w.syl_c = 0;
    INTPTR word_p = 1;

    explode(w.mi.m_szRoot, L"_", c_words);

    for (INTPTR cw = 0; cw < c_words.GetSize(); cw++) {
        
        CFSWString s = c_words[cw];
        s.Replace(L"y", L"õ", 1);
        s = palat_vru(s);
        
        s = word_to_syls(s);
        explode(s, d, temp_arr);
        ss.stress = 0;
        sv_temp.Cleanup();
        for (INTPTR i = 0; i < temp_arr.GetSize(); i++) {
            ss.syl = temp_arr[i];
            ss.stress = 0; // rõhu algväärtus
            ss.word_p = word_p++;
            sv_temp.AddItem(ss);
        }

        add_stress2(sv_temp, cw);
        for (INTPTR i = 0; i < sv_temp.GetSize(); i++)
            sv.AddItem(sv_temp[i]);
    }

    w.syl_vector = sv;

}



