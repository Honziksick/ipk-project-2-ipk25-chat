/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageKeywords.hpp                                           *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  Contains definitions of lowercase string constants for        *
 *               message keywords used in the IPK25 Chat Client.               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageKeywords.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining lowercase string constants for message keywords.
 */

#ifndef MESSAGE_KEYWORDS_HPP
#define MESSAGE_KEYWORDS_HPP

namespace IPK25ChatClient::Constants
{
    /**
     * @class MessageKeywordsLowerCase
     * @brief Provides lowercase string constants for message keywords.
     */
    class MessageKeywordsLowerCase {
    public:
        // Message types in lowercase
        static constexpr auto UNKNOWN_LC = "unknown";  /**< Pseudo-keyword representing an unknown keyword, */
        static constexpr auto CONFIRM_LC = "confirm";  /**< Represents the keyword "confirm". */
        static constexpr auto REPLY_LC = "reply";      /**< Represents the keyword "reply".   */
        static constexpr auto AUTH_LC = "auth";        /**< Represents the keyword "auth".    */
        static constexpr auto JOIN_LC = "join";        /**< Represents the keyword "join".    */
        static constexpr auto MSG_LC = "msg";          /**< Represents the keyword "msg".     */
        static constexpr auto PING_LC = "ping";        /**< Represents the keyword "ping".    */
        static constexpr auto ERR_LC = "err";          /**< Represents the keyword "err".     */
        static constexpr auto BYE_LC = "bye";          /**< Represents the keyword "bye".     */

        // Other message keywords
        static constexpr auto AS_LC = "as";        /**< Represents the keyword "as".    */
        static constexpr auto IS_LC = "is";        /**< Represents the keyword "is".    */
        static constexpr auto OK_LC = "ok";        /**< Represents the keyword "ok".    */
        static constexpr auto NOK_LC = "nok";      /**< Represents the keyword "nok".   */
        static constexpr auto FROM_LC = "from";    /**< Represents the keyword "from".  */
        static constexpr auto USING_LC = "using";  /**< Represents the keyword "using". */
    }; // MessageKeywordsLowerCase
} // IPK25ChatClient::Constants

#endif // MESSAGE_KEYWORDS_HPP

/*** end of file MessageKeywords.hpp ***/
