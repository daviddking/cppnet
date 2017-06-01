#ifndef CPPNET_HTTP_PAGES_H
#define CPPNET_HTTP_PAGES_H

std::string get_page(const std::string &path) {

    if (path == "/Galago") {
        return "<html><head></head><body>"
                "<h1>Galago</h1><hr>"
                "Galagos, also known as bushbabies, bush babies, or nagapies (meaning \"little night monkeys\" in Afrikaans), "
                " are small nocturnal primates native to continental Africa, and make up the family Galagidae "
                "(also sometimes called Galagonidae). They are sometimes included as a subfamily within the Lorisidae"
                " or Loridae."
                "<br>"
                "According to some accounts, the name \"bushbaby\" comes from either the animal's cries or its appearance. "
                "The Afrikaans name nagapie is because they are almost exclusively seen at night, while the Ghanaian "
                "name aposor is given to them because of their firm grip on branches."
                "<br>"
                "In both variety and abundance, the bushbabies are the most successful strepsirrhine primates in Africa, "
                "according to the African Wildlife Foundation."
                "</body></html>";
    } else {
        return
                "<html><head></head><body>"
                        "<h1>Lemur</h1><hr>"
                        "Lemurs are a clade of strepsirrhine primates endemic to the island of Madagascar."
                        " The word lemur derives from the word lemures (ghosts or spirits) from Roman mythology and was first used to "
                        "describe a slender loris due to its nocturnal habits and slow pace, but was later applied to the primates on "
                        "Madagascar. As with other strepsirrhine primates, such as lorises, pottos, and "
                        "<a href=\"Galago\">galagos</a> (bush babies), lemurs "
                        "share resemblance with basal primates. In this regard, lemurs are often confused with ancestral primates, "
                        "when in actuality, lemurs did not give rise to monkeys and apes, but evolved independently."
                        "</body></html>";
    }
}


#endif //CPPNET_HTTP_PAGES_H
