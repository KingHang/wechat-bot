#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <arris/wechat/constant.hpp>
#include <arris/net/net.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using namespace arris::net;


namespace arris {
namespace net {
    class wsserver :public inet{
        using server = websocketpp::server<websocketpp::config::asio>;
        using message_ptr = server::message_ptr;

    public:
        wsserver() {
            server_ = std::make_unique<server>();
            this->port_ = kPort;
        }

        void port(unsigned int port) {
            this->port_ = port;
        }
        ~wsserver() {
            stop();
        }
        void start() {
            try {
                // Set logging settings
                //server_->set_access_channels(websocketpp::log::alevel::all);
                //server_->clear_access_channels(websocketpp::log::alevel::frame_payload);

                // Initialize ASIO
                server_->init_asio();
                server_->set_reuse_addr(true);

                // Register our message handler
                server_->set_message_handler(std::bind(&wsserver::on_message, this, ::_1, ::_2));

                server_->set_http_handler(std::bind(&wsserver::on_http, this, ::_1));
                server_->set_fail_handler(std::bind(&wsserver::on_fail, this, ::_1));
                server_->set_close_handler(std::bind(&wsserver::on_close, this, ::_1));

                server_->set_validate_handler(std::bind(&wsserver::validate, this));

                // Listen on port 
                server_->listen(this->port_);

                // Start the server accept loop
                server_->start_accept();

                // Start the ASIO io_service run loop
                server_->run();

            }
            catch (websocketpp::exception const& e) {
                std::cout << e.what() << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            catch (...) {
                std::cout << "other exception" << std::endl;
            }
        }
        void stop() {
            server_->stop();
        }
    protected:

        bool validate() {
            //sleep(6);
            return true;
        }
        void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
            /*std::cout << "on_message called with hdl: " << hdl.lock().get()
                << " and message: " << msg->get_payload()
                << std::endl;*/
                //__OutputDebugString(TEXT("on_message called with hdl:%d,and message:%s\n"),hdl.lock().get(),msg->get_payload());

                //std::cout << "msg:" <<msg->get_payload() <<std::endl;
            try {
                this->server_->send(hdl, msg->get_payload(), msg->get_opcode());
            }
            catch (websocketpp::exception const& e) {
                std::cout << "Echo failed because: "
                    << "(" << e.what() << ")" << std::endl;
            }
        }
        void on_fail(websocketpp::connection_hdl hdl) {
            server::connection_ptr con = this->server_->get_con_from_hdl(hdl);

            std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message() << std::endl;
        }
        void on_close(websocketpp::connection_hdl) {
            //__OutputDebugString(TEXT("Close handler"));
            std::cout << "Close handler" << std::endl;
        }
        void on_http(websocketpp::connection_hdl hdl) {
            server::connection_ptr con = this->server_->get_con_from_hdl(hdl);

            std::string res = con->get_request_body();

            std::stringstream ss;
            ss << "got HTTP request with " << res.size() << " bytes of body data.";

            con->set_body(ss.str());
            con->set_status(websocketpp::http::status_code::ok);
        }
    private:
        unsigned int port_;
        std::unique_ptr<server> server_;


    };// class wsserver        
}//namespace net
}//namespace arris