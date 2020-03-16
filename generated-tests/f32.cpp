#include <wasm_spec_tests.hpp>

const string wasm_str_f32_0 = base_dir + "/arisen-wasm-spec-tests/generated-tests/wasms/f32.0.wasm";
std::vector<uint8_t> wasm_f32_0= read_wasm(wasm_str_f32_0.c_str());

BOOST_DATA_TEST_CASE(f32_0_pass, boost::unit_test::data::xrange(0,25), index) { try {
   TESTER tester;
   tester.produce_block();
   tester.create_account( N(wasmtest) );
   tester.produce_block();
   tester.set_code(N(wasmtest), wasm_f32_0);
   tester.produce_block();

   action test;
   test.account = N(wasmtest);
   test.name = account_name((uint64_t)index);
   test.authorization = {{N(wasmtest), config::active_name}};

   push_action(tester, std::move(test), N(wasmtest).to_uint64_t());
   tester.produce_block();
   BOOST_REQUIRE_EQUAL( tester.validate(), true );
} FC_LOG_AND_RETHROW() }

