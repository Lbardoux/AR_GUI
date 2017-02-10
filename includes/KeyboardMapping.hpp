/**
 * @file KeyboardMapping.hpp
 * @brief Va permettre de gérer les inputs claviers.
 * @author Laurent BARDOUX p1108365
 */
#ifndef KEYBOARDMAPPING_HPP_INCLUDED
#define KEYBOARDMAPPING_HPP_INCLUDED

#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include "Cv_core.hpp"


/**
 * @class KeyboardMapping
 * @brief Gère les inputs claviers automatiquement.
 */
template<typename Key, typename Callable>
class KeyboardMapping final
{
    public:
        typedef Key                         key_type;   //!< Le type qui sert a mapper une touche du clavier.
        typedef Callable                    entry_type; //!< Le type d'objet appellable (on impose sans argument).
        typedef std::vector<entry_type>     entries;    //!< Un ensemble de ces objets.
        typedef std::map<key_type, entries> mapping;    //!< Le mapping des objets sur les touches.
        
        //! @brief Instancie juste un KeyboardMapping.
        KeyboardMapping(void) noexcept
        {
            
        }
        //! @brief Vide le mapping.
        ~KeyboardMapping(void) noexcept
        {
            this->actions.clear();
        }
        /**
         * @brief Ajoute l'action @b obj pour l'évènement clavier @b k.
         * @param[in] k   L'évènement clavier que l'on veut mapper.
         * @param[in] obj L'action que l'on veut mapper.
         */
        void addAction(const Key& k, Callable obj) noexcept
        {
            typename mapping::iterator it = this->actions.find(k);
            if (it != this->actions.end())
            {
                it->second.push_back(obj);
            }
            else
            {
                this->actions.insert(std::pair<key_type, entries>(k, entries(1, obj)));
            }
        }
        /**
         * @brief Tente les évènements claviers, et appelles les évènements associés
         * si l'évènement clavier est détecté.
         * @param[in] delay Le temps d'attente d'une évènement clavier.
         */
        void checkInputs(int delay)
        {
            char key = cv::waitKey(delay);
            std::for_each(this->actions.begin(), this->actions.end(), [key](typename mapping::value_type& pair){
                if (key == pair.first)
                {
                    std::for_each(pair.second.begin(), pair.second.end(), [](entry_type entry){
                        entry();
                    });
                }
            });
        }
        
    private:
        mapping actions; //!< La table des actions pour les lettres du clavier.
        

        KeyboardMapping(const KeyboardMapping& other)            = delete;
        KeyboardMapping(KeyboardMapping&& other)                 = delete;
        KeyboardMapping& operator=(const KeyboardMapping& other) = delete;
        KeyboardMapping& operator=(KeyboardMapping&& other)      = delete;
        
};



#endif

