/**
 * @file clamp.hpp
 * @brief Offre juste la fonction @b clamp, qui force à rester dans l'intervalle donné en paramètre.
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef CLAMP_HPP_INCLUDED
#define CLAMP_HPP_INCLUDED

#include <algorithm>   // std::max ....
#include <type_traits> // Permet de vérifier si les templates sont cohérents.


/**
 * @brief Remet @b value dans l'intervalle @b min @b max.
 * @param[in,out] value La valeur à borner, qui pourra etre modifier si elle sort des bornes.
 * @param[in]     min   La valeur ... minimale incluse !
 * @param[in]     max   La valeur ... maximale incluse !
 */
template<typename Arithmetic>
Arithmetic& clamp(Arithmetic& value, const Arithmetic& min, const Arithmetic& max) noexcept
{
    static_assert(std::is_arithmetic<Arithmetic>::value, "clamp only accept arithmetic types !");
    value = std::max(min, std::min(max, value));
    return value;
}

#endif
