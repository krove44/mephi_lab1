#include "type_info.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    const char *entity;
    const char *decoded;
} html_entity;

static const html_entity html_code[] = {
{"&nbsp;", " "},
{"&lt;", "<"},
{"&gt;", ">"},
{"&amp;", "&"},
{"&quot;", "\""},
{"&apos;", "'"},
{"&#39;", "'"},

{"&copy;", "©"},
{"&reg;", "®"},
{"&trade;", "™"},
{"&euro;", "€"},
{"&pound;", "£"},
{"&yen;", "¥"},
{"&cent;", "¢"},
{"&sect;", "§"},
{"&para;", "¶"},
{"&middot;", "·"},
{"&bull;", "•"},
{"&hellip;", "..."},
{"&ndash;", "-"},
{"&mdash;", "-"},
{"&laquo;", "«"},
{"&raquo;", "»"},
{"&deg;", "°"},
{"&plusmn;", "±"},
{"&times;", "×"},
{"&divide;", "÷"},
{"&micro;", "µ"},

{"&iexcl;", "¡"},
{"&iquest;", "¿"},
{"&brvbar;", "|"},
{"&not;", "¬"},
{"&shy;", "-"},
{"&macr;", "¯"},
{"&uml;", "¨"},
{"&ordf;", "ª"},
{"&ordm;", "º"},
{"&sup1;", "1"},
{"&sup2;", "2"},
{"&sup3;", "3"},
{"&frac14;", "1/4"},
{"&frac12;", "1/2"},
{"&frac34;", "3/4"},

{"&Agrave;", "À"},
{"&Aacute;", "Á"},
{"&Acirc;", "Â"},
{"&Atilde;", "Ã"},
{"&Auml;", "Ä"},
{"&Aring;", "Å"},
{"&AElig;", "Æ"},
{"&Ccedil;", "Ç"},
{"&Egrave;", "È"},
{"&Eacute;", "É"},
{"&Ecirc;", "Ê"},
{"&Euml;", "Ë"},
{"&Igrave;", "Ì"},
{"&Iacute;", "Í"},
{"&Icirc;", "Î"},
{"&Iuml;", "Ï"},
{"&ETH;", "Ð"},
{"&Ntilde;", "Ñ"},
{"&Ograve;", "Ò"},
{"&Oacute;", "Ó"},
{"&Ocirc;", "Ô"},
{"&Otilde;", "Õ"},
{"&Ouml;", "Ö"},
{"&Oslash;", "Ø"},
{"&Ugrave;", "Ù"},
{"&Uacute;", "Ú"},
{"&Ucirc;", "Û"},
{"&Uuml;", "Ü"},
{"&Yacute;", "Ý"},
{"&THORN;", "Þ"},
{"&szlig;", "ß"},

{"&agrave;", "à"},
{"&aacute;", "á"},
{"&acirc;", "â"},
{"&atilde;", "ã"},
{"&auml;", "ä"},
{"&aring;", "å"},
{"&aelig;", "æ"},
{"&ccedil;", "ç"},
{"&egrave;", "è"},
{"&eacute;", "é"},
{"&ecirc;", "ê"},
{"&euml;", "ë"},
{"&igrave;", "ì"},
{"&iacute;", "í"},
{"&icirc;", "î"},
{"&iuml;", "ï"},
{"&eth;", "ð"},
{"&ntilde;", "ñ"},
{"&ograve;", "ò"},
{"&oacute;", "ó"},
{"&ocirc;", "ô"},
{"&otilde;", "õ"},
{"&ouml;", "ö"},
{"&oslash;", "ø"},
{"&ugrave;", "ù"},
{"&uacute;", "ú"},
{"&ucirc;", "û"},
{"&uuml;", "ü"},
{"&yacute;", "ý"},
{"&thorn;", "þ"},
{"&yuml;", "ÿ"},

{"&Alpha;", "Α"},
{"&Beta;", "Β"},
{"&Gamma;", "Γ"},
{"&Delta;", "Δ"},
{"&Epsilon;", "Ε"},
{"&Zeta;", "Ζ"},
{"&Eta;", "Η"},
{"&Theta;", "Θ"},
{"&Iota;", "Ι"},
{"&Kappa;", "Κ"},
{"&Lambda;", "Λ"},
{"&Mu;", "Μ"},
{"&Nu;", "Ν"},
{"&Xi;", "Ξ"},
{"&Omicron;", "Ο"},
{"&Pi;", "Π"},
{"&Rho;", "Ρ"},
{"&Sigma;", "Σ"},
{"&Tau;", "Τ"},
{"&Upsilon;", "Υ"},
{"&Phi;", "Φ"},
{"&Chi;", "Χ"},
{"&Psi;", "Ψ"},
{"&Omega;", "Ω"},

{"&alpha;", "α"},
{"&beta;", "β"},
{"&gamma;", "γ"},
{"&delta;", "δ"},
{"&epsilon;", "ε"},
{"&zeta;", "ζ"},
{"&eta;", "η"},
{"&theta;", "θ"},
{"&iota;", "ι"},
{"&kappa;", "κ"},
{"&lambda;", "λ"},
{"&mu;", "μ"},
{"&nu;", "ν"},
{"&xi;", "ξ"},
{"&omicron;", "ο"},
{"&pi;", "π"},
{"&rho;", "ρ"},
{"&sigma;", "σ"},
{"&tau;", "τ"},
{"&upsilon;", "υ"},
{"&phi;", "φ"},
{"&chi;", "χ"},
{"&psi;", "ψ"},
{"&omega;", "ω"},

{"&forall;", "∀"},
{"&part;", "∂"},
{"&exist;", "∃"},
{"&empty;", "∅"},
{"&nabla;", "∇"},
{"&isin;", "∈"},
{"&notin;", "∉"},
{"&ni;", "∋"},
{"&prod;", "∏"},
{"&sum;", "∑"},
{"&minus;", "-"},
{"&lowast;", "*"},
{"&radic;", "√"},
{"&prop;", "∝"},
{"&infin;", "∞"},
{"&ang;", "∠"},
{"&and;", "∧"},
{"&or;", "∨"},
{"&cap;", "∩"},
{"&int;", "∫"},
{"&there4;", "∴"},
{"&cong;", "≅"},
{"&asymp;", "≈"},
{"&ne;", "≠"},
{"&equiv;", "≡"},
{"&le;", "≤"},
{"&ge;", "≥"},
{"&sub;", "⊂"},
{"&sup;", "⊃"},
{"&nsub;", "⊄"},
{"&sube;", "⊆"},
{"&supe;", "⊇"},
{"&oplus;", "⊕"},
{"&otimes;", "⊗"},
{"&perp;", "⊥"},
{"&sdot;", "⋅"},

{"&larr;", "←"},
{"&uarr;", "↑"},
{"&rarr;", "→"},
{"&darr;", "↓"},
{"&harr;", "↔"},
{"&crarr;", "↵"},
{"&lArr;", "⇐"},
{"&uArr;", "⇑"},
{"&rArr;", "⇒"},
{"&dArr;", "⇓"},
{"&hArr;", "⇔"},

{"&spades;", "♠"},
{"&clubs;", "♣"},
{"&hearts;", "♥"},
{"&diams;", "♦"}
};

static const size_t html_size() {
    return sizeof(html_code) / sizeof(html_code[0]);
};

static const char* decode_html_entity(const char *entity) {
    for (size_t i = 0; i < html_size(); i++) {
        if (strcmp(entity, html_code[i].entity) == 0) {
            return html_code[i].decoded;
        }
    }
    return NULL;
}

static const char* encode_html_entity(const char *decoded) {
    for (size_t i = 0; i < html_size(); i++) {
        if (strcmp(decoded, html_code[i].decoded) == 0) {
            return html_code[i].entity;
        }
    }
    return NULL;
}

char* decode_html_string(const char* data) {
    size_t len = strlen(data);
    char* result = malloc(len + 1);
    size_t i = 0;
    size_t out = 0;

    while (data[i] != '\0') {
        if (data[i] == '&') {
            const char* html = strchr(data + i, ';');
            if (html != NULL) {
                size_t entity_len = (size_t)(html - (data + i) + 1);
                char entity_buf[32];
                if (entity_len < sizeof(entity_buf)) {
                    memcpy(entity_buf, data + i, entity_len);
                    entity_buf[entity_len] = '\0';
                    const char* decoded = decode_html_entity(entity_buf);
                    if (decoded != NULL) {
                        size_t decoded_len = strlen(decoded);
                        memcpy(result + out, decoded, decoded_len);
                        out += decoded_len;
                        i += entity_len;
                        continue;
                    }
                }
            }
        }
        result[out++] = data[i++];
    }
    result[out] = '\0';
    return result;
}

size_t html_get_next_size(const void* data) {
    const char* str = (const char*)data;
    if (*str == '&') {
        const char* str1 = str + sizeof(char);
        const char* flag = strchr(str1, '&');
        const char* end = strchr(str, ';');
        if (flag && flag < end) {
            return sizeof(char);
        }
        if (end && (end - str) < 10 && (end - str) > 1) {
            return (end - str) + 1;
        }
    }
    return sizeof(char);
}

int html_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

size_t html_length(const void* a) {
    return strlen((const char*)a);
}

void* html_clone(const void* data, size_t l) {
    const char* s = (const char*)data;
    char* copy = malloc(l + 1);
    if (copy) {
        memcpy(copy, s, l);
        copy[l] = '\0';
    }
    return copy;
}

void html_free(void* data) {
    if (data) {
        free(data);
    }
}

bool html_is_delim(const void* data) {
    char p = *(const char*) data;
    return p == ' ' || p == '\n';
}

void html_print(const void* data) {
    const char* str = (const char*)data;
    size_t step = html_get_next_size(data);

    if (*str == '&' && step > 1) {
        char entity_buf[32];
        if (step < sizeof(entity_buf)) {
            memcpy(entity_buf, str, step);
            entity_buf[step] = '\0';

            const char* decoded = decode_html_entity(entity_buf);
            if (decoded != NULL) {
                printf("%s", decoded);
                return;
            }
        }
    }

    printf("%c", *str);
}

type_info html_type = {
    .get_next_size = html_get_next_size,
    .compare = html_compare,
    .get_len = html_length,
    .clone = html_clone,
    .is_delim = html_is_delim,
    .char_size = sizeof(char),
    .free_data = html_free,
    .print = html_print
};

type_info* get_html_type() {
    return &html_type;
}
