#include "Http.hpp"

// This file was written a long time ago for another project of mine.
// NOTE: https://github.com/EdwinS7/UntitledProject/blob/main/Untitled%20Renderer/Include/Core/Utils/Networking/Networking.cpp#L3
size_t WriteCallback( void* contents, size_t size, size_t nmemb, std::string* s ) {
	s->append( ( char* ) contents, size * nmemb );
	return size * nmemb;
}

std::string Http::Get( const char* url ) {
    CURL* Curl = curl_easy_init( );

	if ( !Curl )
		return "";

    std::string Response;

    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    CURLcode Result = curl_easy_perform( Curl );

    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_easy_cleanup( Curl );

    return Response;
}

std::string Http::Post( const char* url, const char* post_data ) {
    CURL* Curl = curl_easy_init( );

    if ( !Curl )
        return "";

    std::string Response;

    curl_easy_setopt( Curl, CURLOPT_POST, 1L );
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_POSTFIELDS, post_data );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    struct curl_slist* headers = NULL;
    headers = curl_slist_append( headers, "Content-Type: application/json" );
    curl_easy_setopt( Curl, CURLOPT_HTTPHEADER, headers );

    CURLcode Result = curl_easy_perform( Curl );

    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_slist_free_all( headers );
    curl_easy_cleanup( Curl );

    return Response;
}

std::string Http::Put( const char* url, const char* put_data ) {
    CURL* Curl = curl_easy_init( );

    if ( !Curl )
        return "";

    std::string Response;

    curl_easy_setopt( Curl, CURLOPT_CUSTOMREQUEST, "PUT" );
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_POSTFIELDS, put_data );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    struct curl_slist* headers = NULL;
    headers = curl_slist_append( headers, "Content-Type: application/json" );
    curl_easy_setopt( Curl, CURLOPT_HTTPHEADER, headers );

    CURLcode Result = curl_easy_perform( Curl );

    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_slist_free_all( headers );
    curl_easy_cleanup( Curl );

    return Response;
}

std::string Http::Delete( const char* url ) {
    CURL* Curl = curl_easy_init( );

    if ( !Curl )
        return "";

    std::string Response;

    curl_easy_setopt( Curl, CURLOPT_CUSTOMREQUEST, "DELETE" );
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    CURLcode Result = curl_easy_perform( Curl );

    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_easy_cleanup( Curl );

    return Response;
}