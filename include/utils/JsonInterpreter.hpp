/*
** EPITECH PROJECT, 2026
** JsonInterpreter
** File description:
** Interpreter for json type file
*/

#ifndef JSONINTERPRETER_HPP_
#define JSONINTERPRETER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

namespace myjson {

    class JsonValue;

    using JsonObject = std::map<std::string, JsonValue>;
    using JsonArray  = std::vector<JsonValue>;
    using JsonNull   = std::nullptr_t;

    class JsonValue {
    private:
        std::variant<JsonNull, bool, double, std::string, JsonArray, JsonObject> m_value;

    public:
        // Constructeurs
        JsonValue() : m_value(nullptr) {}
        JsonValue(bool b) : m_value(b) {}
        JsonValue(double d) : m_value(d) {}
        JsonValue(int i) : m_value(static_cast<double>(i)) {} // Pour gérer les int comme des double
        JsonValue(const std::string& s) : m_value(s) {}
        JsonValue(const char* s) : m_value(std::string(s)) {}
        JsonValue(const JsonArray& a) : m_value(a) {}
        JsonValue(const JsonObject& o) : m_value(o) {}

        // Vérification de types
        bool isNull()   const { return std::holds_alternative<JsonNull>(m_value); }
        bool isBool()   const { return std::holds_alternative<bool>(m_value); }
        bool isNumber() const { return std::holds_alternative<double>(m_value); }
        bool isString() const { return std::holds_alternative<std::string>(m_value); }
        bool isArray()  const { return std::holds_alternative<JsonArray>(m_value); }
        bool isObject() const { return std::holds_alternative<JsonObject>(m_value); }

        template<typename T>
        decltype(auto) get() const {
            if constexpr (std::is_same_v<T, bool>) {
                return static_cast<T>(std::get<bool>(m_value));
            }
            else if constexpr (std::is_arithmetic_v<T>) {
                return static_cast<T>(std::get<double>(m_value));
            }
            else {
                return static_cast<const T&>(std::get<T>(m_value));
            }
        }
        // Accès pour les Objets
        JsonValue& operator[](const std::string& key) {
            if (!isObject()) throw std::runtime_error("Erreur: Le noeud n'est pas un objet JSON.");
            return std::get<JsonObject>(m_value)[key];
        }

        // Accès pour les Tableaux
        JsonValue& operator[](size_t index) {
            if (!isArray()) throw std::runtime_error("Erreur: Le noeud n'est pas un tableau JSON.");
            return std::get<JsonArray>(m_value)[index];
        }
        
        // Tailles (pour arrays et objects)
        size_t size() const {
            if (isArray()) return std::get<JsonArray>(m_value).size();
            if (isObject()) return std::get<JsonObject>(m_value).size();
            return 0;
        }
    };

    // --- LOGIQUE DU PARSEUR ---
    class Parser {
    private:
        std::string m_json;
        size_t m_pos = 0;

        void skipWhitespace() {
            while (m_pos < m_json.length() && std::isspace(m_json[m_pos])) {
                m_pos++;
            }
        }

        std::string parseString() {
            std::string result;
            m_pos++;
            while (m_pos < m_json.size()) {
                if (m_json[m_pos] == '"') {
                    m_pos++;
                    break;
                } else if (m_json[m_pos] == '\\' && m_pos + 1 < m_json.size()) {
                    m_pos++;
                    if (m_json[m_pos] == 'n') result += '\n';
                    else if (m_json[m_pos] == 't') result += '\t';
                    else result += m_json[m_pos];
                } else {
                    result += m_json[m_pos];
                }
                m_pos++;
            }
            return result;
        }

        double parseNumber() {
            size_t start = m_pos;
            while (m_pos < m_json.size() && (std::isdigit(m_json[m_pos]) || m_json[m_pos] == '-' || m_json[m_pos] == '+' || m_json[m_pos] == '.' || m_json[m_pos] == 'e' || m_json[m_pos] == 'E')) {
                m_pos++;
            }
            return std::stod(m_json.substr(start, m_pos - start));
        }

        JsonArray parseArray() {
            JsonArray arr;
            m_pos++;
            skipWhitespace();
            if (m_json[m_pos] == ']') {
                m_pos++;
                return arr;
            }
            while (m_pos < m_json.size()) {
                arr.push_back(parseValue());
                skipWhitespace();
                if (m_json[m_pos] == ']') {
                    m_pos++;
                    break;
                }
                if (m_json[m_pos] == ',') {
                    m_pos++;
                } else {
                    throw std::runtime_error("Erreur de parsing dans le tableau (virgule manquante ?)");
                }
            }
            return arr;
        }

        JsonObject parseObject() {
            JsonObject obj;
            m_pos++;
            skipWhitespace();
            if (m_json[m_pos] == '}') {
                m_pos++;
                return obj;
            }
            while (m_pos < m_json.size()) {
                skipWhitespace();
                std::string key = parseString();
                skipWhitespace();
                
                if (m_json[m_pos] != ':') throw std::runtime_error("Attendu ':' après la clé de l'objet");
                m_pos++;
                
                obj[key] = parseValue();
                skipWhitespace();
                
                if (m_json[m_pos] == '}') {
                    m_pos++;
                    break;
                }
                if (m_json[m_pos] == ',') {
                    m_pos++;
                } else {
                    throw std::runtime_error("Erreur de parsing dans l'objet (virgule manquante ?)");
                }
            }
            return obj;
        }

    public:
        Parser(const std::string& json_str) : m_json(json_str) {}

        JsonValue parseValue() {
            skipWhitespace();
            if (m_pos >= m_json.size()) throw std::runtime_error("Fin de fichier inattendue");

            char c = m_json[m_pos];
            
            if (c == '{') return parseObject();
            if (c == '[') return parseArray();
            if (c == '"') return parseString();
            if (std::isdigit(c) || c == '-') return parseNumber();
            if (m_json.substr(m_pos, 4) == "true") { m_pos += 4; return true; }
            if (m_json.substr(m_pos, 5) == "false") { m_pos += 5; return false; }
            if (m_json.substr(m_pos, 4) == "null") { m_pos += 4; return JsonValue(); }

            throw std::runtime_error(std::string("Caractère inattendu: ") + c);
        }
    };

    // Fonctions utilitaires publiques
    inline JsonValue parse(const std::string& json_string) {
        Parser p(json_string);
        return p.parseValue();
    }

    inline JsonValue parseFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Impossible d'ouvrir le fichier JSON");
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return parse(buffer.str());
    }
}

#endif /* !JSONINTERPRETER_HPP_ */
