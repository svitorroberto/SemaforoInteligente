/*******************************************************************************
 * © Indra Sistemas, S.A.
 * 2013 - 2014  SPAIN
 * 
 * All rights reserved
 ******************************************************************************/
var kp = require('../kpMQTT');
var ssapMessageGenerator = require("../SSAPMessageGenerator");

var myKp = new kp.KpMQTT();
var sessionKey;

//Connect to SIB
myKp.connect('sofia2.com', 1880)
	.then(function() {
		// JOIN Message generation
		var ssapMessageJOIN = ssapMessageGenerator.generateJoinByTokenMessage('b05cde7ef59745f5acd913709d3f298f', 'kpSemaforoInteligente5:WebServer');
		
		return myKp.send(ssapMessageJOIN);
	})
	.then(function(joinResponse) {
		var joinResponseBody = JSON.parse(joinResponse.body);
		
		if (joinResponseBody.ok) {
			sessionKey = joinResponse.sessionKey;
			console.log('Session created with SIB with sessionKey: ' + sessionKey);
		} else {
			throw new Error('Error subscribing to SIB: ' + subscribeResponse.body);
		}

		// INSERT message generation
        var ontologyInstance="{\\\"semaforoInteligente5\\\":{\\\"geometry\\\":{\\\"coordinates\\\":[25.123456,25.123456],\\\"type\\\":\\\"Point\\\"},\\\"id_antena\\\":1,\\\"timestamp\\\":{\\\"$date\\\":\\\"2015-01-30T17:14:00.000Z\\\"},\\\"id_veiculo\\\":\\\"9876\\\",\\\"id_cruzamento\\\":9,\\\"qtd_veiculo\\\":9,\\\"nome_cruzamento\\\":\\\"Av. 1 com Av 2\\\"}}";
		var ssapMessageINSERT = ssapMessageGenerator.generateInsertMessage(ontologyInstance, 'TestSensorTemperatura', sessionKey);
		
		return myKp.send(ssapMessageINSERT);
	})
	.then(function(insertResponse) {
		var insertResponseBody = JSON.parse(insertResponse.body);
		
		if (insertResponseBody.ok) {
			console.log('Ontology Instance inserted in the SIB with ObjectId: ' + insertResponseBody.data);
		} else {
			throw new Error('Error inserting Ontology Instance in the SIB: ' + insertResponse.body);
		}
		
		// LEAVE Message generation
		var ssapMessageLEAVE = ssapMessageGenerator.generateLeaveMessage(sessionKey);

		return myKp.send(ssapMessageLEAVE);
	})
	.then(function(leaveResponse) {
		var leaveResponseBody = JSON.parse(leaveResponse.body);
		
		if (leaveResponseBody.ok) {
			console.log('Session closed with SIB');
		} else {
			console.log('Error closing session with SIB: ' + leaveResponse.body);
		}
	})
	.done(function() {
		//Disconnect from SIB
		myKp.disconnect();
	});