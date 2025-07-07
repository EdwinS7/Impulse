#include "Http.hpp"

// Ts pasted from my old project and it fucking sucks, obviously lmao.
// NOTE: https://github.com/EdwinS7/UntitledProject/blob/main/Untitled%20Renderer/Include/Core/Utils/Networking/Networking.cpp#L3
size_t WriteCallback( void* contents, size_t size, size_t nmemb, std::string* s ) {
	s->append( ( char* ) contents, size * nmemb );
	return size * nmemb;
}

std::string CHttp::Get( const char* url ) {
    CURL* Curl = curl_easy_init( );
	if ( !Curl )
		return "";

    std::string Response;
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    CURLcode Result = curl_easy_perform( Curl );
    if ( FAILED( Result ) )
        std::cerr << "curl_easy_perform failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_easy_cleanup( Curl );

    return Response;
}

std::string CHttp::Post( const char* url, const char* post_data ) {
    CURL* Curl = curl_easy_init( );
    if ( !Curl )
        return "";

    std::string Response;
    curl_easy_setopt( Curl, CURLOPT_POST, 1L );
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_POSTFIELDS, post_data );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    struct curl_slist* Headers = NULL;
    Headers = curl_slist_append( Headers, "Content-Type: application/json" );
    curl_easy_setopt( Curl, CURLOPT_HTTPHEADER, Headers );

    CURLcode Result = curl_easy_perform( Curl );
    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_slist_free_all( Headers );
    curl_easy_cleanup( Curl );

    return Response;
}

std::string CHttp::Put( const char* url, const char* put_data ) {
    CURL* Curl = curl_easy_init( );
    if ( !Curl )
        return "";

    std::string Response;
    curl_easy_setopt( Curl, CURLOPT_CUSTOMREQUEST, "PUT" );
    curl_easy_setopt( Curl, CURLOPT_URL, url );
    curl_easy_setopt( Curl, CURLOPT_WRITEDATA, &Response );
    curl_easy_setopt( Curl, CURLOPT_POSTFIELDS, put_data );
    curl_easy_setopt( Curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    struct curl_slist* Headers = NULL;
    Headers = curl_slist_append( Headers, "Content-Type: application/json" );
    curl_easy_setopt( Curl, CURLOPT_HTTPHEADER, Headers );

    CURLcode Result = curl_easy_perform( Curl );
    if ( Result != CURLE_OK )
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( Result ) << std::endl;

    curl_slist_free_all( Headers );
    curl_easy_cleanup( Curl );

    return Response;
}

std::string CHttp::Delete( const char* url ) {
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

CHttp Http;